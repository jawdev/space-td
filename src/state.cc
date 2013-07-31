#include "config.h"
namespace jaw3d {

///////////////////////////////////////////////// State

State::State() {}

State::~State() {}

//----------------- update

void State::reshape() {}
void State::display() {}

///////////////////////////////////////////////// TestArea

TestArea::TestArea() {}

TestArea::~TestArea() { unload(); }

//----------------- load

void TestArea::load() {
	m_renderbuffer = new Renderbuffer();

	// basic shaders
	ShaderProgram* sprog = new ShaderProgram();
	sprog->load( GL_VERTEX_SHADER, "lighting_basic.vs" ); 
	sprog->load( GL_FRAGMENT_SHADER, "lighting_basic.fs", true );
	sprog->use();
	string uniforms[6] = {
		"m4_camera", "m4_model", "m3_normal",
		"v3_ambient", "v3_light_color", "v3_light_dir"
	};
	sprog->locate_uniforms( uniforms, 6 );
	sprog->debug();
	manager::shaders::load( sprog );

	// lighting
	m_lighting = new Lighting();
	m_lighting->locate_uniform( light_uloc_t::AMBIENT, manager::shaders::uloc( 0, "v3_ambient" ) );
	m_lighting->locate_uniform( light_uloc_t::COLOR, manager::shaders::uloc( 0, "v3_light_color" ) );
	m_lighting->locate_uniform( light_uloc_t::DIRECTION, manager::shaders::uloc( 0, "v3_light_dir" ) );
	m_lighting->color( vec3( 1, 1, 1 ) );
	m_lighting->direction( vec3( 0.2f, -1, -0.4f ) );
	m_lighting->bind();

	// camera
	m_camera = new Camera();
	m_camera->position( vec3( 0, 1.0f, 3.0f ) );
	m_camera->apply_transform();

	// objects
	Object* pObj = new Object();
		pObj->load_shape( new Cube( 0.5f, vec4( 1, 0, 0, 1  )) );
		pObj->locate_uniform( obj_uloc_t::MODEL, manager::shaders::uloc( 0, "m4_model" ) );
		pObj->locate_uniform( obj_uloc_t::NORMAL, 0 );
		pObj->position( vec3( 1, 0, 0 ) )->spin( vec3( 0, 0.1f, 0 ) );
		manager::objects::load( pObj );
	Object* pObj2 = new Object();
		pObj2->load_shape( new Cube( 0.4f, vec4( 0, 1, 0, 1 ) ) );
		pObj2->locate_uniform( obj_uloc_t::MODEL, manager::shaders::uloc( 0, "m4_model" ) );
		pObj2->locate_uniform( obj_uloc_t::NORMAL, 0 );
		pObj2->position( vec3( -1, 0, 0 ) )->spin( vec3( 0.2f, 0, 0.1f ) );
		manager::objects::load( pObj2 );
}

void TestArea::unload() {
	delete m_camera;
	delete m_lighting;
	manager::release_all();
	delete m_renderbuffer;
}

//----------------- update

void TestArea::reshape() {
	float aspect = (float)SETTINGS::height/(float)SETTINGS::width;
	m_camera->projection( vmath::frustum( -1, 1, -aspect, aspect, 1, 500 ) );
	m_camera->bind( manager::shaders::uloc( 0, "m4_camera" ) );
}

void TestArea::display() {
	float dtime = timer::diff();

	// update
	m_renderbuffer->use();
	manager::objects::all_tick( dtime );

	m_renderbuffer->blit();

}

} //jaw3d
