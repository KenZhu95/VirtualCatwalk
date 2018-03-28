R"zzz(#version 330 core
uniform mat4 bone_transform; // transform the cylinder to the correct configuration
const float kPi = 3.1415926535897932384626433832795;
uniform float radius;
uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;
in vec4 vertex_position;

// FIXME: Implement your vertex shader for cylinders
// Note: you need call sin/cos to transform the input mesh to a cylinder

void main() {
	float theta = vertex_position.x * 2 *kPi;
	vec4 local_position = vec4(vertex_position.y, radius * cos(theta), radius * sin(theta), 1.0);
	mat4 transform = projection * view * model * bone_transform;
	gl_Position = transform * local_position;
}
)zzz"
