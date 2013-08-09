#include "config.h"
namespace jaw3d {

///////////////////////////////////////////////// Camera

Camera::Camera( GLint uloc, camera_mode mode, camera_proj proj ) {
	m_uloc = uloc;
	m_mode = mode;
	m_proj = proj;
	default_projection();
}

Camera::~Camera() {}

//----------------- update

void Camera::default_projection() {
	float aspect = (float)SETTINGS::height/(float)SETTINGS::width; 
	switch( m_proj ) {
	case( camera_proj::PERSPECTIVE ):
		m_matProj = vmath::frustum( -1, 1, -aspect, aspect, 1, 500 );
		break;
	case( camera_proj::ORTHOGRAPHIC ):
		cout << "[DEV|NI] Camera::default_projection: ORTHOGRAPHIC" << endl;
		break;
	default:
		return;
	}
}

void Camera::key_move( vec2 v ) {
	cout << "[DEV|NI] Camera::key_move" << endl;
}

void Camera::mouse_spin( vec2 v ) {
	cout << "[DEV|NI] Camera::mouse_spin" << endl;
}

void Camera::zoom( float f ) {
	cout << "[DEV|NI] Camera::zoom" << endl;
}

//----------------- bind

void Camera::bind() {
	if( m_uloc == -1 ) {
		cerr << "Camera::bind> invalid uniform location (" << m_uloc << ")" << endl;
		exit( EXIT_FAILURE );
	}
	m_matRotation = vmath::mat4( vmath::rotate( -m_rotation.z, Z )*vmath::rotate( -m_rotation.y, Y )*vmath::rotate( -m_rotation.x, X ) );
	m_matTranslation = vmath::mat4( vmath::translate( -m_position.x, -m_position.y, -m_position.z ) );
	m_matTransform = m_matTranslation*m_matRotation;
	m_matFinal = m_matProj*m_matTransform;
	glUniformMatrix4fv( m_uloc, 1, GL_FALSE, m_matFinal );
} 

//----------------- set

Camera* Camera::mode( camera_mode m ) { m_mode = m; return this; }
Camera* Camera::proj( camera_proj p ) { m_proj = p; return this; }
Camera* Camera::position( vec3 v ) { m_position = v; return this; }
Camera* Camera::rotation( vec3 v ) { m_rotation = v; return this; }
Camera* Camera::mat_final( vmath::vec4 mat ) { m_matFinal = mat; return this; }
Camera* Camera::mat_transform( vmath::vec4 mat ) { m_matTransform = mat; return this; }
Camera* Camera::mat_proj( vmath::vec4 mat ) { m_matProj = mat; return this; }
Camera* Camera::mat_translation( vmath::vec4 mat ) { m_matTranslation = mat; return this; }
Camera* Camera::mat_rotation( vmath::vec4 mat ) { m_matRotation = mat; return this; }
Camera* Camera::uloc( GLint i ) { m_uloc = i; return this; }

//----------------- get

camera_mode Camera::mode() { return m_mode; }
camera_proj Camera::proj() { return m_proj; }
vec3 Camera::position() { return m_position; }
vec3 Camera::rotation() { return m_rotation; }
vmath::mat4 Camera::mat_final() { return m_matFinal; }
vmath::mat4 Camera::mat_transform() { return m_matTransform; }
vmath::mat4 Camera::mat_proj() { return m_matProj; }
vmath::mat4 Camera::mat_translation() { return m_matTranslation; }
vmath::mat4 Camera::mat_rotation() { return m_matRotation; }
GLint Camera::uloc() { return m_uloc; }

} //jaw3d
