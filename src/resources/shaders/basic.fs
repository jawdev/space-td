#version 330 core

in vec4 vs_fs_color; 

layout (location=0) out vec4 fColor;

void main() {
	fColor = vs_fs_color;
}
