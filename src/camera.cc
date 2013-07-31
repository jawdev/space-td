#include "config.h"
namespace jaw3d {

///////////////////////////////////////////////// Camera

Camera::Camera() {}

Camera::~Camera() {}

//----------------- update

void Camera::apply_transform() {
	vmath::mat4 rot = vmath::mat4( vmath::rotate( -m_rotation.z, Z )*vmath::rotate( -m_rotation.y, Y )*vmath::rotate( -m_rotation.x, X ) );
	vmath::mat4 trans = vmath::mat4( vmath::translate( -m_position.x, -m_position.y, -m_position.z ) );
	m_matrix = trans*rot;
}

void Camera::bind( GLint uloc ) {
	if( uloc == -1 ) {
		cerr << "Camera::bind> invalid uniform location (" << uloc << ")" << endl;
		exit( EXIT_FAILURE );
	}
	glUniformMatrix4fv( uloc, 1, GL_FALSE, m_projection*m_matrix );
} 

//----------------- update

void Camera::matrix( vmath::mat4 mat ) { m_matrix = mat; }
void Camera::projection( vmath::mat4 mat ) { m_projection = mat; }
void Camera::position( vec3 v ) { m_position = v; }
void Camera::rotation( vec3 v ) { m_rotation = v; }

} //jaw3d
