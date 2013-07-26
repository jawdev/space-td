#include "config.h"

bool SETTINGS::debug = true;
string SETTINGS::title = "Space TD";
unsigned int SETTINGS::width = 800;
unsigned int SETTINGS::height = 600;
string SETTINGS::path_resources = "resources/";
string SETTINGS::path_shaders = SETTINGS::path_resources+"shaders/";

//---------------------------- TEMPORARY

Camera* g_camera;
Lighting *g_lighting;

enum { Color, Depth, NumRenderbuffers };
GLuint framebuffer, renderbuffer[NumRenderbuffers];

//---------------------------- helpers

void reshape( int w, int h ) {
	glViewport( 0, 0, w, h );
	SETTINGS::width = w;
	SETTINGS::height = h;

	// update projection
	float aspect = (float)SETTINGS::height/(float)SETTINGS::width;
	g_camera->projection( vmath::frustum( -1, 1, -aspect, aspect, 1, 500 ) );
	g_camera->bind( manager::shaders::uloc( 0, "m4_camera" ) );
}

void display() {
	float dtime = timer::diff();

	// update
	manager::objects::all_update( dtime );

	glBindFramebuffer( GL_DRAW_FRAMEBUFFER, framebuffer );
	glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
	
	manager::objects::all_bind_render();

	glBindFramebuffer( GL_READ_FRAMEBUFFER, framebuffer );
	glBindFramebuffer( GL_DRAW_FRAMEBUFFER, 0 );
	glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
	glBlitFramebuffer( 0, 0, SETTINGS::width-1, SETTINGS::height-1, 0, 0, SETTINGS::width-1, SETTINGS::height-1, GL_COLOR_BUFFER_BIT, GL_NEAREST );

	// swap
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void keyboard( unsigned char key, int x, int y ) {
	switch( key ) {
	case 27:
		exit( 0 );
		break;
	}
}

void quit() {
	delete g_lighting;
	delete g_camera;
	manager::release_all();
}


//---------------------------- init

int main( int argc, char* argv[] ) {
	if( !Setup::init_glut( &argc, argv ) ) exit( EXIT_FAILURE );
	if( !Setup::create_window( SETTINGS::width, SETTINGS::height, SETTINGS::title.c_str() ) ) exit( EXIT_FAILURE );
	if( !Setup::init_glew() ) exit( EXIT_FAILURE );
	glClearColor( 0.2f, 0.0f, 0.2f, 1.0f );

	// TEMP - render buffer
	glGenRenderbuffers( NumRenderbuffers, renderbuffer );
	glBindRenderbuffer( GL_RENDERBUFFER, renderbuffer[Color] );
	glRenderbufferStorage( GL_RENDERBUFFER, GL_RGBA, SETTINGS::width, SETTINGS::height );
	glBindRenderbuffer( GL_RENDERBUFFER, renderbuffer[Depth] );
	glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, SETTINGS::width, SETTINGS::height );
	glGenFramebuffers( 1, &framebuffer );
	glBindFramebuffer( GL_DRAW_FRAMEBUFFER, framebuffer );
	glFramebufferRenderbuffer( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderbuffer[Color] );
	glFramebufferRenderbuffer( GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderbuffer[Depth] );
	glEnable( GL_DEPTH_TEST );

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
	g_lighting = new Lighting();
	g_lighting->locate_uniform( light_uloc_t::AMBIENT, manager::shaders::uloc( 0, "v3_ambient" ) );
	g_lighting->locate_uniform( light_uloc_t::COLOR, manager::shaders::uloc( 0, "v3_light_color" ) );
	g_lighting->locate_uniform( light_uloc_t::DIRECTION, manager::shaders::uloc( 0, "v3_light_dir" ) );
	g_lighting->color( vec3( 1, 1, 1 ) );
	g_lighting->direction( vec3( 0.2f, -1, -0.4f ) );
	g_lighting->bind();

	// camera
	g_camera = new Camera();
	g_camera->position( vec3( 0, 1.0f, 3.0f ) );
	g_camera->apply_transform();

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

	// load glut procedures
	glutReshapeFunc( reshape );
	glutDisplayFunc( display );
	glutKeyboardFunc( keyboard );

	// glut main loop
	atexit( quit );
	glutMainLoop();
}
