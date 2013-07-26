#include "config.h"
namespace jaw3d {

///////////////////////////////////////////////// Object

Object::Object() {
	m_shape = NULL;
	m_update = m_render = true;
	m_uniforms = new GLint[(unsigned int)obj_uloc_t::LEN];
	for( unsigned int i = 0; i < (unsigned int)obj_uloc_t::LEN; i++ ) m_uniforms[i] = -1;
}

Object::~Object() {
	if( m_shape != NULL ) delete m_shape;
	delete [] m_uniforms;
}

//----------------- load

void Object::load_shape( Shape* pShape ) {
	if( m_shape != NULL ) delete m_shape;
	m_shape = pShape;
}

void Object::locate_uniform( obj_uloc_t type, GLint loc ) {
	m_uniforms[(unsigned int)type] = loc;
}

//----------------- update

void Object::update( float dtime ) {
	if( !m_update || dtime == 0 ) return;
	m_position += m_velocity*dtime;
	m_rotation += m_spin*dtime;
	m_scale += m_dscale*dtime;
}

void Object::bind() {
	if( !m_render ) return;
	if( m_shape != NULL ) m_shape->bind();

	unsigned int loc_model = (unsigned int)obj_uloc_t::MODEL;
	unsigned int loc_normal = (unsigned int)obj_uloc_t::NORMAL;

	if( m_uniforms[loc_model] != -1 || m_uniforms[loc_normal] != -1 ) {

		// model matrix
		vmath::mat4 rot = vmath::mat4( vmath::rotate( m_rotation.z, Z )*vmath::rotate( m_rotation.y, Y )*vmath::rotate( m_rotation.x, X ) );
		vmath::mat4 trans = vmath::mat4( vmath::translate( m_position.x, m_position.y, m_position.z ) );
		vmath::mat4 model = trans*rot;
		if( m_uniforms[loc_model] != -1 ) glUniformMatrix4fv( m_uniforms[loc_model], 1, GL_FALSE, model );

		// normal matrix
		GLfloat normal[] = {
			-model[0][0], -model[0][1], -model[0][2],
			-model[1][0], -model[1][1], -model[1][2],
			-model[2][0], -model[2][1], -model[2][2]
		};
		if( m_uniforms[loc_normal] != -1 ) glUniformMatrix3fv( m_uniforms[loc_normal], 1, GL_FALSE, normal );
		
	}

	
}

void Object::render() {
	if( !m_render ) return;
	if( m_shape != NULL ) m_shape->render();
}

void Object::bind_render() {
	bind();
	render();
}

//----------------- set

Object* Object::allow_update( bool b ) { m_update = b; return this; }
Object* Object::allow_render( bool b ) { m_render = b; return this; }
Object* Object::position( vec3 v ) { m_position = v; return this; }
Object* Object::rotation( vec3 v ) { m_rotation = v; return this; }
Object* Object::velocity( vec3 v ) { m_velocity = v; return this; }
Object* Object::spin( vec3 v ) { m_spin = v; return this; }
Object* Object::dscale( vec3 v ) { m_dscale = v; return this; }

//----------------- get

bool Object::allow_update() { return m_update; }
bool Object::allow_render() { return m_render; }
vec3 Object::position() { return m_position; }
vec3 Object::rotation() { return m_rotation; }
vec3 Object::scale() { return m_spin; }
vec3 Object::velocity() { return m_velocity; }
vec3 Object::spin() { return m_spin; }
vec3 Object::dscale() { return m_dscale; }

}
