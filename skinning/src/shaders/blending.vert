R"zzz(
#version 330 core
uniform vec4 light_position;
uniform vec3 camera_position;

uniform vec3 joint_trans[128];
uniform vec4 joint_rot[128];
uniform vec3 joint_init_trans[128];

in int jid0;
in int jid1;
in float w0;
in vec3 vector_from_joint0;
in vec3 vector_from_joint1;
in vec4 normal;
in vec2 uv;
in vec4 vert;

out vec4 vs_light_direction;
out vec4 vs_normal;
out vec2 vs_uv;
out vec4 vs_camera_direction;

vec3 qtransform(vec4 q, vec3 v) {
	return v + 2.0 * cross(cross(v, q.xyz) - q.w*v, q.xyz);
}

/*vec4 constructDualR(vec4 q, vec3 v) {
	vec4 dual = vec4(1.0);
	dual[0] = q[0];
	dual[1] = q[1];
	dual[2] = q[2];
	dual[3] = q[3];
	return dual;
}*/

vec4 constructDualI(vec4 q, vec3 v){
	vec4 dual = vec4(1.0);
	dual[0] = -0.5 * (v[0]*q.x  + v[1]*q.y + v[2]*q.z);
	dual[1] =  0.5 * (v[0]*q.w  + v[1]*q.z - v[2]*q.y);
	dual[2] =  0.5 * (-v[0]*q.z + v[1]*q.w + v[2]*q.x);
	dual[3] =  0.5 * (v[0]*q.y  - v[1]*q.x + v[2]*q.w);
	return dual;
}

vec3 toTrans(vec4 dual_r, vec4 dual_i){
	vec3 trans = vec3(1.0);
	trans[0] = 2.0*(-dual_i[0]*dual_r.x + dual_i[1]*dual_r.w - dual_i[2]*dual_r.z + dual_i[3]*dual_r.y);
	trans[1] = 2.0*(-dual_i[0]*dual_r.y + dual_i[1]*dual_r.z + dual_i[2]*dual_r.w - dual_i[3]*dual_r.x);
	trans[2] = 2.0*(-dual_i[0]*dual_r.z - dual_i[1]*dual_r.y + dual_i[2]*dual_r.x + dual_i[3]*dual_r.w);
	return trans;
}


void main() {
	// FIXME: Implement linear skinning here

	vec3 position_0 = qtransform(joint_rot[jid0], vector_from_joint0) + joint_trans[jid0];
	vec3 position_1 = qtransform(joint_rot[jid1], vector_from_joint1) + joint_trans[jid1];
	//gl_Position = vec4( w0 * position_0 +  (1-w0) * position_1, 1.0 );

	vec3 trans_0 =  joint_trans[jid0] - qtransform(joint_rot[jid0], vert.xyz - vector_from_joint0);
	vec3 trans_1 =  joint_trans[jid1] - qtransform(joint_rot[jid1], vert.xyz - vector_from_joint1);
	vec4 dual_r_0 = joint_rot[jid0];
	vec4 dual_i_0 = constructDualI(joint_rot[jid0], trans_0);

	vec4 dual_r_1 = joint_rot[jid1];
	vec4 dual_i_1 = constructDualI(joint_rot[jid1], trans_1);

	vec4 dual_r = w0 * dual_r_0 + (1-w0) * dual_r_1;
	vec4 dual_i = w0 * dual_i_0 + (1-w0) * dual_i_1;
	float mag = sqrt(dual_r.w * dual_r.w + dual_r.x * dual_r.x + dual_r.y * dual_r.y + dual_r.z * dual_r.z);
	dual_r = dual_r / mag;
	dual_i = dual_i / mag;

	vec3 new_trans = toTrans(dual_r, dual_i);
	gl_Position = vec4(qtransform(dual_r, vert.xyz) + new_trans, 1.0);
	/*float wo = dual_r[0];
	float xo = dual_r[1];
	float yo = dual_r[2];
	float zo = dual_r[3];
	float we = dual_i[0];
	float xe = dual_i[1];
	float ye = dual_i[2];
	float ze = dual_i[3];
	float t0 = 2 * (-we*xo + xe*wo - ye*zo + ze*yo);
	float t1 = 2 * (-we*yo + xe*zo + ye*wo - ze*xo);
	float t2 = 2 * (-we*zo - xe*yo + ye*xo + ze*wo);
	float M00 = 1 - 2*yo*yo - 2*zo*zo;
	float M01 = 2*xo*yo - 2*wo*zo;
	float M02 = 2*xo*zo + 2*wo*yo;
	float M03 = t0;
	float M10 = 2*xo*yo + 2*wo*zo;
	float M11 = 1 - 2*xo*xo - 2*zo*zo;
	float M12 = 2*yo*zo - 2*wo*xo;
	float M13 = t1;
	float M20 = 2*xo*zo - 2*wo*yo;
	float M21 = 2*yo*zo + 2*wo*xo;
	float M22 = 1 - 2*xo*xo - 2*yo*yo;
	float M23 = t2;
	float v0 = M00*vert.x + M01*vert.y + M02*vert.z + M03;
	float v1 = M10*vert.x + M11*vert.y + M12*vert.z + M13;
	float v2 = M20*vert.x + M21*vert.y + M22*vert.z + M23;*/
	//gl_Position = vec4(v0, v1, v2, 1.0);


	//gl_Position = vert;
	vs_normal = normal;
	vs_light_direction = light_position - gl_Position;
	vs_camera_direction = vec4(camera_position, 1.0) - gl_Position;
	vs_uv = uv;
}
)zzz"
