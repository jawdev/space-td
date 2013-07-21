#include "config.h"
namespace jaw3d {

///////////////////////////////////////////////// Object

Object::Object() {
	m_shape = NULL;
}

Object::~Object() {
	if( m_shape != NULL ) delete m_shape;
}

//----------------- load

void Object::load_shape( Shape* pShape ) {
	if( m_shape != NULL ) delete m_shape;
	m_shape = pShape;
}

//----------------- update

void Object::update( float dtime ) {
	if( dtime == 0 ) return;
	m_position += m_velocity*dtime;
	m_rotation += m_spin*dtime;
	m_scale += m_dscale*dtime;
}

void Object::bind() {
	if( m_shape != NULL ) m_shape->bind();
	vmath::mat4 rot = vmath::mat4( vmath::rotate( m_rotation.z, Z )*vmath::rotate( m_rotation.y, Y )*vmath::rotate( m_rotation.x, X ) );
	vmath::mat4 trans = vmath::mat4( vmath::translate( m_position.x, m_position.y, m_position.z ) );
	vmath::mat4 model = trans*rot;
	glUniformMatrix4fv( GLOBAL::shaderPrograms.get( 0 )->uloc( "m4_model" ), 1, GL_FALSE, model );
}

void Object::render() {
	if( m_shape != NULL ) m_shape->render();
}

//----------------- set

void Object::position( vec3 v ) { m_position = v; }
void Object::rotation( vec3 v ) { m_rotation = v; }
void Object::velocity( vec3 v ) { m_velocity = v; }
void Object::spin( vec3 v ) { m_spin = v; }
void Object::dscale( vec3 v ) { m_dscale = v; }

//----------------- get

vec3 Object::position() { return m_position; }
vec3 Object::rotation() { return m_rotation; }
vec3 Object::scale() { return m_spin; }
vec3 Object::velocity() { return m_velocity; }
vec3 Object::spin() { return m_spin; }
vec3 Object::dscale() { return m_dscale; }

}
