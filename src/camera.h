#ifndef __CAMERA_H__
#define __CAMERA_H__
namespace jaw3d {

///////////////////////////////////////////////// Camera

class Camera {
public:
	Camera();
	~Camera();

	// update
	void apply_transform();
	void bind( GLint uloc );

	// set
	void matrix( vmath::mat4 );
	void position( vec3 );
	void rotation( vec3 );
	
private:
	vec3 m_position;
	vec3 m_rotation;
	vmath::mat4 m_matrix;
};

}
#endif //__CAMERA_H__
