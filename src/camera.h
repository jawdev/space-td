#ifndef __CAMERA_H__
#define __CAMERA_H__
namespace jaw3d {

///////////////////////////////////////////////// Camera

enum class camera_mode { STATIC, UFO, FOCUSED, FIXED };
enum class camera_proj { PERSPECTIVE, ORTHOGRAPHIC };

class Camera {
public:
	Camera( GLint uloc, camera_mode=camera_mode::STATIC, camera_proj=camera_proj::PERSPECTIVE );
	~Camera();

	// update
	void default_projection();
	void key_move( vec2 );
	void mouse_spin( vec2 );
	void zoom( float );

	// bind
	void bind();

	// set
	Camera* mode( camera_mode );
	Camera* proj( camera_proj );
	Camera* position( vec3 );
	Camera* rotation( vec3 );
	Camera* mat_final( vmath::vec4 );
	Camera* mat_transform( vmath::vec4 );
	Camera* mat_proj( vmath::vec4 );
	Camera* mat_translation( vmath::vec4 );
	Camera* mat_rotation( vmath::vec4 );
	Camera* uloc( GLint );

	// get
	camera_mode mode();
	camera_proj proj();
	vec3 position();
	vec3 rotation();
	vmath::mat4 mat_final();
	vmath::mat4 mat_transform();
	vmath::mat4 mat_proj();
	vmath::mat4 mat_translation();
	vmath::mat4 mat_rotation();
	GLint uloc();
private:
	camera_mode m_mode;
	camera_proj m_proj;
	vec3 m_position;
	vec3 m_rotation;
	vmath::mat4 m_matFinal;
	vmath::mat4 m_matTransform;
	vmath::mat4 m_matProj;
	vmath::mat4 m_matTranslation;
	vmath::mat4 m_matRotation;
	GLint m_uloc;
};

}
#endif //__CAMERA_H__
