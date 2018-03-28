#include "config.h"
#include "bone_geometry.h"
#include <fstream>
#include <queue>
#include <iostream>
#include <stdexcept>
#include <glm/gtx/io.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

/*
 * For debugging purpose.
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
	size_t count = std::min(v.size(), static_cast<size_t>(10));
	for (size_t i = 0; i < count; ++i) os << i << " " << v[i] << "\n";
	os << "size = " << v.size() << "\n";
	return os;
}

std::ostream& operator<<(std::ostream& os, const BoundingBox& bounds)
{
	os << "min = " << bounds.min << " max = " << bounds.max;
	return os;
}



// FIXME: Implement bone animation.


void Skeleton::refreshCache()
{
	joint_rot.resize(joints.size());
	joint_trans.resize(joints.size());
	joint_init_trans.resize(joints.size());
	bone_transforms.resize(bones.size());
	for (size_t i = 0; i < bones.size(); i++) {
		if (bones[i] != nullptr){
			bone_transforms[i] = bones[i]->getCylinderTransform();
			joints[bones[i]->parent_index].orientation = bones[i]->orientation;
		}
		
	}
	//joints[0].position = glm::vec3(bones[1]->translation[3][0], bones[1]->translation[3][1],bones[1]->translation[3][2]);
	for (size_t i = 0; i < joints.size(); i++) {
		if (joints[i].parent_index != -1){
			joints[i].position = glm::vec3(bones[i]->deformed_transform * glm::inverse(bones[i]->undeformed_transform) * glm::vec4(joints[i].init_position,1.0));
		} else {
			int root_child = joints[i].children[0];
			joints[i].position = glm::vec3(bones[root_child]->translation[3][0], bones[root_child]->translation[3][1],bones[root_child]->translation[3][2]);
		}
		
	}

	for (size_t i = 0; i < joints.size(); i++) {
		joint_rot[i] = joints[i].orientation;
		joint_trans[i] = joints[i].position;
		joint_init_trans[i] = joints[i].init_position;
	}


}

const glm::vec3* Skeleton::collectJointTrans() const
{
	return joint_trans.data();
}

const glm::vec3* Skeleton::collectJointInitTrans() const
{
	return joint_init_trans.data();
}

const glm::fquat* Skeleton::collectJointRot() const
{
	return joint_rot.data();
}

const glm::mat4* Skeleton::collectBoneTransforms() const
{
	return bone_transforms.data();
}

const glm::mat4* Skeleton::getBoneTransform(int bone_id) const
{
	return &bone_transforms[bone_id];
}

void Skeleton::doTranslation(glm::vec3 diff_translation, int root_id){
	Joint root = joints[root_id];
	for (size_t i = 0; i < root.children.size(); i++){
		bones[root.children[i]]->performTranslation(diff_translation);
	}
}

Bone* Skeleton::getBone(int bone_id)
{
	return bones[bone_id];
}

void Skeleton::constructBone(int joint_id)
{
	if (joint_id <= 0 || bones[joint_id] != nullptr){
		return;
	}


	Joint end_j = joints[joint_id];
	if (end_j.parent_index == -1){
		bones[joint_id] = nullptr;
		return;
	}
	Joint start_j = joints[end_j.parent_index];
	Bone *bone = new Bone(start_j, end_j);
	joints[end_j.parent_index].children.emplace_back(end_j.joint_index);
	bones[joint_id] = bone;
	glm::vec3 diff;
	if (start_j.parent_index >= 0){
		bone->parent = bones[end_j.parent_index];
		diff = start_j.position - joints[start_j.parent_index].position;
	} else {
		bone->parent = nullptr;
		diff = start_j.position;
	}
	bone->translation = glm::mat4(1.0f);
	bone->translation[3][0] = diff.x;
	bone->translation[3][1] = diff.y;
	bone->translation[3][2] = diff.z;
	if (start_j.parent_index == -1){
		bone->undeformed_transform = bone->translation;
		bone->deformed_transform = bone->translation * glm::toMat4(glm::normalize(bone->rel_orientation));
		bone->root_joint_index = start_j.joint_index;
	} else {
		bone->undeformed_transform = (bone->parent)->undeformed_transform * bone->translation;
		bone->deformed_transform = (bone->parent)->deformed_transform * bone->translation * glm::toMat4(glm::normalize(bone->rel_orientation));
		bone->root_joint_index = bone->parent->root_joint_index;

	}
	if (bone->parent != nullptr) {
		bone->parent->children.emplace_back(bone);
	}
	
	
}

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

void Mesh::loadPmd(const std::string& fn)
{
	MMDReader mr;
	mr.open(fn);
	mr.getMesh(vertices, faces, vertex_normals, uv_coordinates);
	computeBounds();
	mr.getMaterial(materials);

	// FIXME: load skeleton and blend weights from PMD file,
	//        initialize std::vectors for the vertex attributes,
	//        also initialize the skeleton as needed
	int id = 0;
	int parent = 0;
	glm::vec3 wcoord;

	while (mr.getJoint(id, wcoord, parent)){
		Joint joint = Joint(id, wcoord, parent);
		skeleton.joints.emplace_back(joint);
		id++;
	}

	skeleton.bones.resize(skeleton.joints.size());
	for (uint i = 0 ; i < skeleton.joints.size(); i++){
		if (skeleton.joints[i].parent_index == -1){
			skeleton.bones[i] = nullptr;
		}
	}
	//skeleton.bones[0] = nullptr;

	for (uint i = 1; i < skeleton.joints.size(); i++){
		skeleton.constructBone(i);
	}


	std::vector<SparseTuple> weights;
	mr.getJointWeights(weights);

	for (SparseTuple& sparse_tuple : weights) {
		int v_id = sparse_tuple.vid;
		joint0.emplace_back(sparse_tuple.jid0);
		joint1.emplace_back(sparse_tuple.jid1);
		weight_for_joint0.emplace_back(sparse_tuple.weight0);
		vector_from_joint0.emplace_back(glm::vec3(vertices[v_id]) - skeleton.joints[sparse_tuple.jid0].position);
		vector_from_joint1.emplace_back(glm::vec3(vertices[v_id]) - skeleton.joints[sparse_tuple.jid1].position);

	}
}

void Mesh::updateAnimation()
{
	skeleton.refreshCache();
}

int Mesh::getNumberOfBones() const
{
	return skeleton.joints.size();
}

Bone* Mesh::getBone(int bone_id){
	return skeleton.getBone(bone_id);
}

void Mesh::computeBounds()
{
	bounds.min = glm::vec3(std::numeric_limits<float>::max());
	bounds.max = glm::vec3(-std::numeric_limits<float>::max());
	for (const auto& vert : vertices) {
		bounds.min = glm::min(glm::vec3(vert), bounds.min);
		bounds.max = glm::max(glm::vec3(vert), bounds.max);
	}
}



glm::mat4 Bone::getTranslation(){
	return translation;
}

glm::mat4 Bone::getUndeformed(){
	return undeformed_transform;
}

glm::mat4 Bone::getDeformed(){
	return deformed_transform;
}

glm::fquat Bone::getOrientation(){
	return orientation;
}

glm::fquat Bone::getRelOrientation(){
	return rel_orientation;
}


glm::vec4 Bone::boneAlign(glm::vec4 bone_coor){
	return alignMatrix * bone_coor;
}

glm::mat4 Bone::getCylinderTransform(){
	glm::mat4 trans = deformed_transform * inverseAlignMatrix;
	glm::mat4 scale = glm::mat4(1.0f);
	scale[0][0] = length;
	return trans * scale;
}

void Bone::performRotate(glm::fquat rotate_quat){
	glm::mat4 previous_rel = glm::toMat4(rel_orientation);
	glm::mat4 previous_ori = glm::toMat4(orientation);
	glm::mat4 update_rel = glm::toMat4(rotate_quat) * previous_rel;
	glm::mat4 update_ori = glm::toMat4(rotate_quat) * previous_ori;
	rel_orientation = glm::normalize(glm::toQuat(update_rel));
	orientation = glm::normalize(glm::toQuat(update_ori));

	deformed_transform = deformed_transform * glm::inverse(previous_rel) * update_rel;

	for (size_t i=0; i < children.size(); i++){
		children[i]->performParentRotate();
	}
}

void Bone::performRotateTotal(glm::fquat rotate_quat){
	if (parent != nullptr){
		for (size_t i = 0; i < parent->children.size(); i++){
			Bone* child = parent->children[i];
			child->performRotate(rotate_quat);
		}
	} else {
		performRotate(rotate_quat);
	}
}


void Bone::performParentRotate() {
	deformed_transform = parent->deformed_transform * translation * glm::toMat4(rel_orientation);
	glm::mat4 update_ori = glm::toMat4(parent->orientation) * glm::toMat4(rel_orientation);
	orientation = glm::normalize(glm::toQuat(update_ori));
	for (size_t i=0; i < children.size(); i++){
		children[i]->performParentRotate();
	}
}

void Bone::performTranslation(glm::vec3 diff_translation){
	translation[3][0] += 20.0f * diff_translation.x;
	translation[3][1] += 20.0f * diff_translation.y;
	translation[3][2] += 20.0f * diff_translation.z;
	deformed_transform = translation * glm::toMat4(glm::normalize(rel_orientation));
	for (size_t i=0; i < children.size(); i++){
		children[i]->performParentTranslation();
	}
}

void Bone::performParentTranslation() {
	deformed_transform = parent->deformed_transform * translation * glm::toMat4(glm::normalize(rel_orientation));
	for (size_t i=0; i < children.size(); i++){
		children[i]->performParentTranslation();
	}
}

