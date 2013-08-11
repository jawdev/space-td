#include "config.h"
namespace jaw3d {

///////////////////////////////////////////////// State

State::State() {
	m_userInput = nullptr;
}

State::~State() {}

//----------------- load

void State::load() {}
void State::unload() {}

//----------------- update

void State::reshape() {}
void State::display() {}

//----------------- get

UserInput* State::user_input() { return m_userInput; }

///////////////////////////////////////////////// TestArea

TestArea::TestArea() {}

TestArea::~TestArea() { unload(); }

//----------------- load

void TestArea::load() {
	m_time = 0;
	m_fps = new tools::fps_tracker();
	m_renderbuffer = new Renderbuffer();
	m_userInput = new UserInput();

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
	manager::shaders::load( sprog );

	// lighting
	m_light = new DirectionLight( vec3( 0.2f, -1, -0.4f ), vec3( 1, 1, 1 ) );
	m_light->locate_uniform( light_uloc_t::AMBIENT, manager::shaders::uloc( 0, "v3_ambient" ) );
	m_light->locate_uniform( light_uloc_t::COLOR, manager::shaders::uloc( 0, "v3_light_color" ) );
	m_light->locate_uniform( light_uloc_t::DIRECTION, manager::shaders::uloc( 0, "v3_light_dir" ) );
	m_light->bind();

	// camera
	m_camera = new Camera( manager::shaders::uloc( 0, "m4_camera" ) );
	m_camera->focus( vec3(), 5.0f );

	// objects
	GLint loc_model = manager::shaders::uloc( 0, "m4_model" );
	GLint loc_normal = manager::shaders::uloc( 0, "m3_normal" );
	Object* pObj = new Object();
		pObj->load_shape( new Sphere( 1, 10, vec4( 1, 0, 0, 1 ) ) );
		pObj->locate_uniform( obj_uloc_t::MODEL, loc_model );
		pObj->locate_uniform( obj_uloc_t::NORMAL, loc_normal );
		manager::objects::load( pObj, "obj" );
	Object* pObj2 = new Object();
		pObj2->load_shape( new FloorPlane( 5, 5, vec4( 1, 1, 1, 1 ) ) );
		pObj2->locate_uniform( obj_uloc_t::MODEL, loc_model );
		pObj2->locate_uniform( obj_uloc_t::NORMAL, loc_normal );
		pObj2->position( vec3( 0, -2, 0 ) );
		manager::objects::load( pObj2, "plane" );
	Object* pObj3 = new Object();
		pObj3->load_shape( new Cube( 0.5f, vec4( 0, 1, 0, 1 ) ) );
		pObj3->locate_uniform( obj_uloc_t::MODEL, loc_model );
		pObj3->locate_uniform( obj_uloc_t::NORMAL, loc_normal );
		pObj3->position( vec3( 0, 2, 0 ) );
		manager::objects::load( pObj3, "obj2" );

	// OpenGL parameters
}

void TestArea::unload() {
	manager::objects::clear();
	manager::shaders::clear();

	delete m_fps;
	delete m_renderbuffer;
	delete m_camera;
	delete m_userInput;
	delete m_light;

	m_userInput = nullptr;
}

//----------------- update

void TestArea::reshape() {
	// update renderbuffer
	m_renderbuffer->resize();

	// update projection transform
	m_camera->bind();
}

void TestArea::display() {
	if( m_userInput->key_event( 27u, key_event_t::DOWN ) ) exit( 0 );
	float mdx = (float)( ( m_userInput->keydown( 'a' )?-1:0 )+( m_userInput->keydown( 'd' )?1:0 ) );
	float mdy = (float)( ( m_userInput->keydown( 'w' )?1:0 )+( m_userInput->keydown( 's' )?-1:0 ) );
	if( mdx != 0 || mdy != 0 ) {
		m_camera->spin( mdx, mdy );
		m_camera->bind();
	}

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
	m_userInput->flush();
}

} //jaw3d
