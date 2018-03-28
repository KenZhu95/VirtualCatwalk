#include "gui.h"
#include "config.h"
#include <jpegio.h>
#include "bone_geometry.h"
#include <iostream>
#include <debuggl.h>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace {
	// FIXME: Implement a function that performs proper
	//        ray-cylinder intersection detection
	// TIPS: The implement is provided by the ray-tracer starter code.

	const float RAY_EPSILON = 0.00000001;



	bool intersectBody(const glm::vec3& origin, const glm::vec3& direction, 
	float height, float radius, float* t){
		float y0 = origin[1];
		float z0 = origin[2];
		float y1 = direction[1];
		float z1 = direction[2];

		float a = y1*y1 + z1*z1;
		float b = 2.0*(y0*y1 + z0*z1);
		float c = y0*y0 + z0*z0 - radius * radius;

		if( 0.0 == a ) {
			// This implies that y1 = 0.0 and z1 = 0.0, which further
			// implies that the ray is aligned with the body of the cylinder,
			// so no intersection.
			return false;
		}

		float discriminant = b*b - 4.0*a*c;

		if( discriminant < 0.0 ) {
			return false;
		}
		
		discriminant = sqrt( discriminant );

		float t2 = (-b + discriminant) / (2.0 * a);

		if( t2 <= RAY_EPSILON ) {
			return false;
		}

		float t1 = (-b - discriminant) / (2.0 * a);

		if (t1 > RAY_EPSILON){
			//Two intersections.
			glm::vec3 P = origin + direction * t1;
			float x = P[0];
			if (x >= 0.0 && x <= height){
				//It's okay.
				*t = t1;
				return true;
			}
		}

		glm::vec3 P = origin +  direction * t2;
		float x = P[0];
		if (x >= 0.0 && x <= height){
			*t = t2;
			return true;
		}

		return false;
	}

	bool intersectCaps(const glm::vec3& origin, const glm::vec3& direction, 
	float height, float radius, float* t){
		float ox = origin[0];
		float dx = direction[0];

		if (0.0 == dx){
			return false;
		}

		float t1;
		float t2;

		if (dx > 0.0){
			t1 = (-ox)/dx;
			t2 = (height-ox)/dx;
		} else {
			t1 = (height-ox)/dx;
			t2 = (-ox)/dx;
		}

		if (t2 < RAY_EPSILON){
			return false;
		}

		if (t1 >= RAY_EPSILON){
			glm::vec3 p = origin +  direction * t1;
			if ((p[1]*p[1] + p[2]*p[2]) <= radius * radius){
				*t = t1;
				return true;
			}
		}


		glm::vec3 p = origin +  direction * t2;
		if ((p[1]*p[1] + p[2]*p[2]) <= radius * radius){
			*t = t2;
			return true;
		}

		return false;

	}

	bool intersectCylinder(const glm::vec3& origin, const glm::vec3& direction, 
	float height, float radius, float* t){
		if (intersectCaps(origin, direction, height, radius, t)){
			float tt;
			if (intersectBody(origin, direction, height, radius, &tt)){
				if (tt < (*t)){
					*t = tt;
				}
			}
			return true;
		} else {
			return intersectBody(origin, direction, height, radius, t);
		}
	}
}

GUI::GUI(GLFWwindow* window)
	:window_(window)
{
	glfwSetWindowUserPointer(window_, this);
	glfwSetKeyCallback(window_, KeyCallback);
	glfwSetCursorPosCallback(window_, MousePosCallback);
	glfwSetMouseButtonCallback(window_, MouseButtonCallback);

	glfwGetWindowSize(window_, &window_width_, &window_height_);
	float aspect_ = static_cast<float>(window_width_) / window_height_;
	projection_matrix_ = glm::perspective((float)(kFov * (M_PI / 180.0f)), aspect_, kNear, kFar);
}

GUI::~GUI()
{
}

void GUI::assignMesh(Mesh* mesh)
{
	mesh_ = mesh;
	center_ = mesh_->getCenter();
}

void GUI::keyCallback(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window_, GL_TRUE);
		return ;
	}
	if (key == GLFW_KEY_J && action == GLFW_RELEASE) {
		//FIXME save out a screenshot using SaveJPEG
		GLubyte *pixel = (GLubyte*)malloc(4 * window_width_ * window_height_);
		glReadPixels(0, 0, window_width_, window_height_, GL_RGB, GL_UNSIGNED_BYTE, pixel);
		SaveJPEG("output.jpg", window_width_, window_height_, pixel);
		free(pixel);
	}

	if (captureWASDUPDOWN(key, action))
		return ;
	if (key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT) {
		float roll_speed;
		if (key == GLFW_KEY_RIGHT)
			roll_speed = -roll_speed_;
		else
			roll_speed = roll_speed_;
		// FIXME: actually roll the bone here
		if (current_bone_ == -1){
			return;
		}
		Bone *bone = mesh_->getBone(current_bone_);
		glm::mat4 rotate_matrix = glm::rotate(roll_speed, bone->direction);
		glm::fquat rotate_quat = glm::toQuat(rotate_matrix);
		bone->performRotateTotal(rotate_quat);
		mesh_->updateAnimation();

	} else if (key == GLFW_KEY_C && action != GLFW_RELEASE) {
		fps_mode_ = !fps_mode_;
	} else if (key == GLFW_KEY_LEFT_BRACKET && action == GLFW_RELEASE) {
		current_bone_--;
		current_bone_ += mesh_->getNumberOfBones();
		current_bone_ %= mesh_->getNumberOfBones();
	} else if (key == GLFW_KEY_RIGHT_BRACKET && action == GLFW_RELEASE) {
		current_bone_++;
		current_bone_ += mesh_->getNumberOfBones();
		current_bone_ %= mesh_->getNumberOfBones();
	} else if (key == GLFW_KEY_T && action != GLFW_RELEASE) {
		transparent_ = !transparent_;
	} else if (key == GLFW_KEY_Q && action != GLFW_RELEASE) {
		translation_mode_ = !translation_mode_;
	}
}

void GUI::mousePosCallback(double mouse_x, double mouse_y)
{
	last_x_ = current_x_;
	last_y_ = current_y_;
	current_x_ = mouse_x;
	current_y_ = window_height_ - mouse_y;
	float delta_x = current_x_ - last_x_;
	float delta_y = current_y_ - last_y_;
	if (sqrt(delta_x * delta_x + delta_y * delta_y) < 1e-15)
		return;
	glm::vec3 mouse_direction = glm::normalize(glm::vec3(delta_x, delta_y, 0.0f));
	glm::vec2 mouse_start = glm::vec2(last_x_, last_y_);
	glm::vec2 mouse_end = glm::vec2(current_x_, current_y_);
	glm::uvec4 viewport = glm::uvec4(0, 0, window_width_, window_height_);

	bool drag_camera = drag_state_ && current_button_ == GLFW_MOUSE_BUTTON_RIGHT;
	bool drag_bone = drag_state_ && current_button_ == GLFW_MOUSE_BUTTON_LEFT;

	if (drag_camera) {
		glm::vec3 axis = glm::normalize(
				orientation_ *
				glm::vec3(mouse_direction.y, -mouse_direction.x, 0.0f)
				);
		orientation_ =
			glm::mat3(glm::rotate(rotation_speed_, axis) * glm::mat4(orientation_));
		tangent_ = glm::column(orientation_, 0);
		up_ = glm::column(orientation_, 1);
		look_ = glm::column(orientation_, 2);
	} else if (drag_bone && current_bone_ != -1) {
		// FIXME: Handle bone rotation
		if (!translation_mode_){
			Bone *bone = mesh_->getBone(current_bone_);
			glm::vec3 start_rotate = glm::unProject(glm::vec3(mouse_start, 0.0f), view_matrix_ * model_matrix_, projection_matrix_, viewport);
			glm::vec3 end_rotate = glm::unProject(glm::vec3(mouse_end, 0.0f), view_matrix_ * model_matrix_, projection_matrix_, viewport);
			glm::vec3 diff_rotate = glm::normalize(glm::cross(end_rotate - start_rotate, look_));
			// glm::vec3 parent_p = bone->start->position;
			// glm::vec3 proj_parent_p = glm::project(parent_p, view_matrix_, projection_matrix_, viewport);
			// glm::vec2 start_diff = glm::normalize(glm::vec2(last_x_ - proj_parent_p.x, last_y_ - proj_parent_p.y));
			// glm::vec2 end_diff = glm::normalize(glm::vec2(current_x_ - proj_parent_p.x, current_y_ - proj_parent_p.y));
			// float angle_diff = glm::angle(start_diff, end_diff);
			// if (start_diff.x - end_diff.x > 0){
			// 	angle_diff = angle_diff;
			// } else {
			// 	angle_diff = -angle_diff;
			// }
			//glm::vec3 diff_rotate = glm::normalize(glm::cross(look_, glm::vec3(mouse_direction.y, -mouse_direction.x, 0.0f)));
			glm::mat4 rotate_matrix = glm::rotate(rotation_speed_, diff_rotate);
			glm::fquat rotate_quat = glm::normalize(glm::toQuat(rotate_matrix));
			bone->performRotateTotal(rotate_quat);
			mesh_->updateAnimation();
			return;
		} else {
			Bone *bone = mesh_->getBone(current_bone_);
			// if (bone->start->parent_index == -1){
			// 	return;
			// }
			int root_id = bone->root_joint_index;
			glm::vec3 start_translation = glm::unProject(glm::vec3(mouse_start, 0.0f), view_matrix_ * model_matrix_, projection_matrix_, viewport);
			glm::vec3 end_translation = glm::unProject(glm::vec3(mouse_end, 0.0f), view_matrix_ * model_matrix_, projection_matrix_, viewport);
			glm::vec3 diff_translation = end_translation - start_translation;
			mesh_->skeleton.doTranslation(diff_translation, root_id);
			mesh_->updateAnimation();
		}
		return ;
	}

	// FIXME: highlight bones that have been moused over
	current_bone_ = -1;
	glm::vec3 world_coord_near = glm::unProject(glm::vec3(current_x_, current_y_, 0.0f), view_matrix_ * model_matrix_, projection_matrix_, viewport);
	glm::vec3 position_ray = getCamera();
	glm::vec3 direction_ray = glm::normalize(world_coord_near - position_ray);
	
	float t = 100000000;
	for (int i = 1; i < mesh_->getNumberOfBones(); i++){
		Bone* bone = mesh_->skeleton.bones[i];
		glm::vec4 bone_origin = glm::vec4(mesh_->skeleton.joints[bone->parent_index].position, 1.0f);
		glm::vec4 bone_ray_position = bone->worldToBone(glm::vec4(position_ray, 1.0f));
		glm::vec4 bone_ray_direction = bone->worldToBone(glm::vec4(direction_ray, 0.0f));
		glm::vec4 bone_ray_position_t = bone->boneAlign(bone_ray_position);
		glm::vec4 bone_ray_direction_t = bone->boneAlign(bone_ray_direction);

		float tt;
		if (intersectCylinder(glm::vec3(bone_ray_position_t), glm::vec3(bone_ray_direction_t), bone->length, kCylinderRadius, &tt)){
			if (tt < t){
				if (setCurrentBone(i)){
					//std::cout << "set current bone success" << bone->bone_index << std::endl;
				} else {
					//std::cout << "set current bone faliure" << bone->bone_index << std::endl;
				}
			}
		}
		

	}
}

void GUI::mouseButtonCallback(int button, int action, int mods)
{
	drag_state_ = (action == GLFW_PRESS);
	current_button_ = button;
}

void GUI::updateMatrices()
{
	// Compute our view, and projection matrices.
	if (fps_mode_)
		center_ = eye_ + camera_distance_ * look_;
	else
		eye_ = center_ - camera_distance_ * look_;

	view_matrix_ = glm::lookAt(eye_, center_, up_);
	light_position_ = glm::vec4(eye_, 1.0f);

	aspect_ = static_cast<float>(window_width_) / window_height_;
	projection_matrix_ =
		glm::perspective((float)(kFov * (M_PI / 180.0f)), aspect_, kNear, kFar);
	model_matrix_ = glm::mat4(1.0f);
}

MatrixPointers GUI::getMatrixPointers() const
{
	MatrixPointers ret;
	ret.projection = &projection_matrix_[0][0];
	ret.model= &model_matrix_[0][0];
	ret.view = &view_matrix_[0][0];
	return ret;
}

bool GUI::setCurrentBone(int i)
{
	if (i < 0 || i >= mesh_->getNumberOfBones())
		return false;
	current_bone_ = i;
	return true;
}


bool GUI::captureWASDUPDOWN(int key, int action)
{
	if (key == GLFW_KEY_W) {
		if (fps_mode_)
			eye_ += zoom_speed_ * look_;
		else
			camera_distance_ -= zoom_speed_;
		return true;
	} else if (key == GLFW_KEY_S) {
		if (fps_mode_)
			eye_ -= zoom_speed_ * look_;
		else
			camera_distance_ += zoom_speed_;
		return true;
	} else if (key == GLFW_KEY_A) {
		if (fps_mode_)
			eye_ -= pan_speed_ * tangent_;
		else
			center_ -= pan_speed_ * tangent_;
		return true;
	} else if (key == GLFW_KEY_D) {
		if (fps_mode_)
			eye_ += pan_speed_ * tangent_;
		else
			center_ += pan_speed_ * tangent_;
		return true;
	} else if (key == GLFW_KEY_DOWN) {
		if (fps_mode_)
			eye_ -= pan_speed_ * up_;
		else
			center_ -= pan_speed_ * up_;
		return true;
	} else if (key == GLFW_KEY_UP) {
		if (fps_mode_)
			eye_ += pan_speed_ * up_;
		else
			center_ += pan_speed_ * up_;
		return true;
	}
	return false;
}


// Delegrate to the actual GUI object.
void GUI::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	GUI* gui = (GUI*)glfwGetWindowUserPointer(window);
	gui->keyCallback(key, scancode, action, mods);
}

void GUI::MousePosCallback(GLFWwindow* window, double mouse_x, double mouse_y)
{
	GUI* gui = (GUI*)glfwGetWindowUserPointer(window);
	gui->mousePosCallback(mouse_x, mouse_y);
}

void GUI::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	GUI* gui = (GUI*)glfwGetWindowUserPointer(window);
	gui->mouseButtonCallback(button, action, mods);
}

float GUI::vector_2d_angle(glm::vec2 a, glm::vec2 b){
	float inner = a.x * b.x + a.y * b.y;
	float det = a.x * b.y - a.y * b.x;
	float angle = glm::acos(inner);
	if (det > 0){
		return angle;
	} else {
		return -angle;
	}

}
