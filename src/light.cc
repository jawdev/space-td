#include "config.h"
namespace jaw3d {

///////////////////////////////////////////////// Light

Light::Light() {
	m_uniforms = new GLint[(unsigned int)light_uloc_t::_LEN];
	for( unsigned int i = 0; i < (unsigned int)light_uloc_t::_LEN; i++ ) m_uniforms[i] = -1;
}

Light::~Light() {
	delete [] m_uniforms;
}

//----------------- update

void Light::locate_uniform( light_uloc_t type, GLint i ) {
	m_uniforms[(unsigned int)type] = i;
	if( SETTINGS::debug ) cout << "[DEBUG] Light::locate_uniform> light_uloc_t[" << (unsigned int)type << "]=" << i << endl;
}

void Light::bind() {}

///////////////////////////////////////////////// DirectionLight

DirectionLight::DirectionLight( vec3 direction, vec3 color ) {
	m_direction = direction;
	m_color = color;
}

DirectionLight::~DirectionLight() {
	
}

//----------------- update

void DirectionLight::bind() {
	unsigned int k;

	// ambient
	k = (unsigned int)light_uloc_t::AMBIENT;
	if( m_uniforms[k] != -1 ) {
		vmath::vec3 v( m_ambient.x, m_ambient.y, m_ambient.z );
		glUniform3fv( m_uniforms[k], 1, v );
	}

	// color
	k = (unsigned int)light_uloc_t::COLOR;
	if( m_uniforms[k] != -1 ) {
		vmath::vec3 v( m_color.x, m_color.y, m_color.z );
		glUniform3fv( m_uniforms[k], 1, v );
	}

	// direction
	k = (unsigned int)light_uloc_t::DIRECTION;
	if( m_uniforms[k] != -1 ) {
		vmath::vec3 v( m_direction.x, m_direction.y, m_direction.z );
		glUniform3fv( m_uniforms[k], 1, v );
	}
}

//----------------- set

DirectionLight* DirectionLight::ambient( vec3 v ) { m_ambient = v; return this; }
DirectionLight* DirectionLight::color( vec3 v ) { m_color = v; return this; }
DirectionLight* DirectionLight::direction( vec3 v ) { m_direction = v; return this; }

//----------------- get

vec3 DirectionLight::ambient() { return m_ambient; }
vec3 DirectionLight::color() { return m_color; }
vec3 DirectionLight::direction() { return m_direction; }


} //jaw3d
