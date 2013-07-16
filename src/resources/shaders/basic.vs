#version 330 core

uniform mat4 m4_projection;
uniform mat4 m4_model;
uniform float f_tmp;

layout (location=0) in vec4 position;
layout (location=1) in vec4 color;

out vec4 vs_fs_color;

void main( void ) {
	vs_fs_color = color;
	gl_Position = m4_projection*( m4_model*position );
}
