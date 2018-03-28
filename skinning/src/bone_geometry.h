#ifndef BONE_GEOMETRY_H
#define BONE_GEOMETRY_H

#include <iostream>
#include <ostream>
#include <vector>
#include <map>
#include <limits>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/io.hpp>
#include <glm/gtx/transform.hpp>
#include <mmdadapter.h>

struct BoundingBox {
	BoundingBox()
		: min(glm::vec3(-std::numeric_limits<float>::max())),
		max(glm::vec3(std::numeric_limits<float>::max())) {}
	glm::vec3 min;
	glm::vec3 max;
};

struct Joint {
	Joint()
		: joint_index(-1),
		  parent_index(-1),
		  position(glm::vec3(0.0f)),
		  init_position(glm::vec3(0.0f))
	{
	}
	Joint(int id, glm::vec3 wcoord, int parent)
		: joint_index(id),
		  parent_index(parent),
		  position(wcoord),
		  init_position(wcoord)
	{
	}

	int joint_index;
	int parent_index;
	glm::vec3 position;             // position of the joint
	glm::fquat orientation;         // rotation w.r.t. initial configuration
	glm::fquat rel_orientation;     // rotation w.r.t. it's parent. Note: it's not necessary to align the local coord sys. with the bone direction. So it could be initialized as identity.
	glm::vec3 init_position;        // initial position of this joint
	std::vector<int> children;
};

struct LineMesh {
	std::vector<glm::vec4> vertices;
	std::vector<glm::uvec2> indices;
};


struct Bone{
	Bone(Joint j_start, Joint j_end){
		start = &j_start;
		end = &j_end;
		bone_index = j_end.joint_index;
		parent_index = j_start.joint_index;
		length = glm::length(j_end.position - j_start.position);
		direction = glm::normalize(j_end.position - j_start.position);
		if (direction.x != 0){
			normal_y = glm::normalize(glm::cross(direction, glm::vec3(0.0,1.0,0.0)));
		} else {
			normal_y = glm::normalize(glm::cross(direction, glm::vec3(1.0,0.0,0.0)));
		}
		normal_z = glm::normalize(glm::cross(direction, normal_y));
		alignMatrix = glm::mat4(1.0);
		alignMatrix[0][0] = direction[0];
		alignMatrix[1][0] = direction[1];
		alignMatrix[2][0] = direction[2];
		alignMatrix[0][1] = normal_y[0];
		alignMatrix[1][1] = normal_y[1];
		alignMatrix[2][1] = normal_y[2];
		alignMatrix[0][2] = normal_z[0];
		alignMatrix[1][2] = normal_z[1];
		alignMatrix[2][2] = normal_z[2];
		inverseAlignMatrix = glm::mat4(1.0);
		inverseAlignMatrix[0][0] = direction[0];
		inverseAlignMatrix[0][1] = direction[1];
		inverseAlignMatrix[0][2] = direction[2];
		inverseAlignMatrix[1][0] = normal_y[0];
		inverseAlignMatrix[1][1] = normal_y[1];
		inverseAlignMatrix[1][2] = normal_y[2];
		inverseAlignMatrix[2][0] = normal_z[0];
		inverseAlignMatrix[2][1] = normal_z[1];
		inverseAlignMatrix[2][2] = normal_z[2];

		orientation = glm::fquat(1.0,0.0,0.0,0.0);
		rel_orientation = glm::fquat(1.0,0.0,0.0,0.0);
	}

	glm::mat4 getTranslation();

	glm::mat4 getUndeformed();

	glm::mat4 getDeformed();

	glm::fquat getOrientation();

	glm::fquat getRelOrientation();

	glm::vec4 boneToWorld(glm::vec4 bone_coor){
		return deformed_transform * bone_coor;
	}

	glm::vec4 worldToBone(glm::vec4 world_coor){
		return glm::inverse(deformed_transform) * world_coor;
	}

	glm::vec4 boneAlign(glm::vec4 bone_coor);

	glm::mat4 getCylinderTransform();

	void performRotateTotal(glm::fquat rotate_quat);
	void performRotate(glm::fquat rotate_quat);
	void performParentRotate();
	void performTranslation(glm::vec3 diff_translation);
	void performParentTranslation();


	int bone_index;
	int parent_index;
	int root_joint_index;
	Joint* start;
	Joint* end;
	float length;
	Bone* parent;
	std::vector<Bone*> children;
	glm::mat4 translation;               // translation matrix of bone w.r.t parent
	glm::mat4 undeformed_transform;      // undoformed transformation matrix
	glm::mat4 deformed_transform;        // deformed transformation matrix
	glm::fquat rel_orientation;          // rotation w.r.t its parent
	glm::fquat orientation;              // rotation w.r.t. initial configuration
	glm::vec3 direction;                 // direction of bone (x axis)
	glm::vec3 normal_y;                  // normal direction (y axis)
	glm::vec3 normal_z;                  // another normal direction (z axis)
	glm::mat4 alignMatrix;               // matrix to align local coordinates along with bone direction
	glm::mat4 inverseAlignMatrix;        // matrix to transform from bone direction to initial local coordinates 
};

struct Skeleton {
	std::vector<Joint> joints;
	std::vector<Bone*> bones;

	std::vector<glm::vec3> joint_trans; // cache for uniforms
	std::vector<glm::fquat> joint_rot; // cache for uniforms
	std::vector<glm::vec3> joint_init_trans; // cache for uniforms

	void refreshCache();
	const glm::vec3* collectJointTrans() const;
	const glm::vec3* collectJointInitTrans() const;
	const glm::fquat* collectJointRot() const;

	// FIXME: create skeleton and bone data structures
	void constructBone(int joint_id);
	Bone* getBone(int bone_id);

	std::vector<glm::mat4> bone_transforms;
	const glm::mat4* collectBoneTransforms() const;
	const glm::mat4* getBoneTransform(int bone_id) const;
	void doTranslation(glm::vec3 diff_translation, int roor_id);
};

struct Mesh {
	Mesh();
	~Mesh();
	std::vector<glm::vec4> vertices;
	/*
	 * Static per-vertex attrributes for Shaders
	 */
	std::vector<int32_t> joint0;
	std::vector<int32_t> joint1;
	std::vector<float> weight_for_joint0; // weight_for_joint1 can be calculated
	std::vector<glm::vec3> vector_from_joint0;
	std::vector<glm::vec3> vector_from_joint1;
	std::vector<glm::vec4> vertex_normals;
	std::vector<glm::vec4> face_normals;
	std::vector<glm::vec2> uv_coordinates;
	std::vector<glm::uvec3> faces;

	std::vector<Material> materials;
	BoundingBox bounds;
	Skeleton skeleton;

	void loadPmd(const std::string& fn);
	void updateAnimation();
	int getNumberOfBones() const;
	glm::vec3 getCenter() const { return 0.5f * glm::vec3(bounds.min + bounds.max); }
	Bone* getBone(int bone_id);
private:
	void computeBounds();
	void computeNormals();

};


#endif
