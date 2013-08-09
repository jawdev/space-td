#include "config.h"
namespace jaw3d {

///////////////////////////////////////////////// State

State::State() {}
State::~State() {}

//----------------- load
void State::load() {}
void State::unload() {}
void State::key( unsigned char k, bool down ) {}

//----------------- update

void State::reshape() {}
void State::display() {}

///////////////////////////////////////////////// TestArea

TestArea::TestArea() {}

TestArea::~TestArea() { unload(); }

//----------------- load

void TestArea::load() {
	m_time = 0;
	m_fps = new tools::fps_tracker();
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
	m_camera = new Camera( manager::shaders::uloc( 0, "m4_camera" ) );
	m_camera->position( vec3( 0, 3.0f, 10.0f ) );

	// objects
	GLint loc_model = manager::shaders::uloc( 0, "m4_model" );
	GLint loc_normal = manager::shaders::uloc( 0, "m3_normal" );
	Object* pObj = new Object();
		pObj->load_shape( new Cube( 0.5f, vec4( 1, 0, 0, 1 ) ) );
		pObj->locate_uniform( obj_uloc_t::MODEL, loc_model );
		pObj->locate_uniform( obj_uloc_t::NORMAL, loc_normal );
		pObj->position( vec3( 1, 2, 0 ) )->spin( vec3( 0, 0.1f, 0 ) );
		manager::objects::load( pObj, "cube" );
	Object* pObj2 = new Object();
		pObj2->load_shape( new FloorPlane( 5, 5, vec4( 1, 1, 1, 1 ) ) );
		pObj2->locate_uniform( obj_uloc_t::MODEL, loc_model );
		pObj2->locate_uniform( obj_uloc_t::NORMAL, loc_normal );
		manager::objects::load( pObj2, "plane" );
}

void TestArea::unload() {
	manager::objects::clear();
	manager::shaders::clear();

	delete m_fps;
	delete m_renderbuffer;
	delete m_camera;
	delete m_lighting;
}

//----------------- update

void TestArea::reshape() {
	// update renderbuffer
	m_renderbuffer->resize();

	// update projection transform
	m_camera->bind();
}

void TestArea::display() {
	float dtime = timer::diff();
	m_time += dtime;
	if( m_time > 1 ) {
		m_fps->supply( dtime );
		float avg = m_fps->average();
		cout << "dtime: " << avg << "s, fps: " << 1.0f/avg << endl;
		m_time = 0;
	}

	// update
	m_renderbuffer->use();
	manager::objects::all_tick( dtime );

	m_renderbuffer->blit();

}

} //jaw3d
