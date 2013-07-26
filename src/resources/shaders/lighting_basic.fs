#version 330 core

uniform vec3 v3_ambient;
uniform vec3 v3_light_color;
uniform vec3 v3_light_dir;

in vec4 fs_v4_color; 
in vec3 fs_v3_normal;

layout (location=0) out vec4 frag_color;

void main() {
	float diffuse = max( 0.0, dot( fs_v3_normal, v3_light_dir ) );
	vec3 scatteredLight = v3_ambient+v3_light_color*diffuse;
	vec3 rgb = min( fs_v4_color.rgb*scatteredLight, vec3( 1.0 ) );
	frag_color = vec4( rgb, fs_v4_color.a );
}
