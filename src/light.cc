#include "config.h"
namespace jaw3d {

///////////////////////////////////////////////// Lighting

Lighting::Lighting() {
	m_uniforms = new GLint[(unsigned int)light_uloc_t::LEN];
	for( unsigned int i = 0; i < (unsigned int)light_uloc_t::LEN; i++ ) m_uniforms[i] = -1;
}

Lighting::~Lighting() {}

//----------------- update

void Lighting::locate_uniform( light_uloc_t type, GLint loc ) {
	m_uniforms[(unsigned int)type] = loc;
	if( SETTINGS::debug ) cout << "[DEBUG] Lighting::locate_uniform> light_uloc_t[" << (unsigned int)type << "]=" << loc << endl;
}

void Lighting::bind() {
	unsigned int k;

	// ambient
	k = (unsigned int)light_uloc_t::AMBIENT;
	if( m_uniforms[k] != -1 ) {
		vmath::vec3 v( m_ambient.x, m_ambient.y, m_ambient.z );
		glUniform3fv( m_uniforms[k], 1, v );
		if( SETTINGS::debug ) cout << "[DEBUG] Lighting::bind> light_uloc_t[" << k << "] OK" << endl;
	} else if( SETTINGS::debug ) cout << "[DEBUG] Lighting::bind> light_uloc_t[" << k << "] FAILED" << endl;

	// color
	k = (unsigned int)light_uloc_t::COLOR;
	if( m_uniforms[k] != -1 ) {
		vmath::vec3 v( m_color.x, m_color.y, m_color.z );
		glUniform3fv( m_uniforms[k], 1, v );
		if( SETTINGS::debug ) cout << "[DEBUG] Lighting::bind> light_uloc_t[" << k << "] OK" << endl;
	} else if( SETTINGS::debug ) cout << "[DEBUG] Lighting::bind> light_uloc_t[" << k << "] FAILED" << endl;

	// direction
	k = (unsigned int)light_uloc_t::DIRECTION;
	if( m_uniforms[k] != -1 ) {
		vmath::vec3 v( m_direction.x, m_direction.y, m_direction.z );
		glUniform3fv( m_uniforms[k], 1, v );
		if( SETTINGS::debug ) cout << "[DEBUG] Lighting::bind> light_uloc_t[" << k << "] OK" << endl;
	} else if( SETTINGS::debug ) cout << "[DEBUG] Lighting::bind> light_uloc_t[" << k << "] FAILED" << endl;
}

//----------------- set

Lighting* Lighting::ambient( vec3 v ) { m_ambient = v; return this; }
Lighting* Lighting::color( vec3 v ) { m_color = v; return this; }
Lighting* Lighting::direction( vec3 v ) { m_direction = v; return this; }

//----------------- get

vec3 Lighting::ambient() { return m_ambient; }
vec3 Lighting::color() { return m_color; }
vec3 Lighting::direction() { return m_direction; }


} //jaw3d
