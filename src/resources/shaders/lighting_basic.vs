#version 330 core

uniform mat4 m4_camera;
uniform mat4 m4_model;
uniform mat3 m3_normal;

layout (location=0) in vec4 v4_position;
layout (location=1) in vec3 v3_normal;
layout (location=2) in vec4 v4_color;

out vec4 fs_v4_color;
out vec3 fs_v3_normal;

void main( void ) {
	fs_v4_color = v4_color;
	fs_v3_normal = normalize( m3_normal*v3_normal );
	gl_Position = m4_camera*m4_model*v4_position;
}
