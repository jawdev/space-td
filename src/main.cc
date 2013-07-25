#include "config.h"

string SETTINGS::title = "Space TD";
unsigned int SETTINGS::width = 800;
unsigned int SETTINGS::height = 600;
string SETTINGS::path_resources = "resources/";
string SETTINGS::path_shaders = SETTINGS::path_resources+"shaders/";

//---------------------------- TEMPORARY

float g_time = 0;

enum { Color, Depth, NumRenderbuffers };
GLuint framebuffer, renderbuffer[NumRenderbuffers];

//---------------------------- helpers

void reshape( int w, int h ) {
	glViewport( 0, 0, w, h );
	SETTINGS::width = w;
	SETTINGS::height = h;

	// update projection
	float aspect = (float)SETTINGS::height/(float)SETTINGS::width;
	vmath::mat4 proj = vmath::frustum( -1, 1, -aspect, aspect, 1, 500 );
	glUniformMatrix4fv( manager::shaders::uloc( "basic", "m4_projection" ), 1, GL_FALSE, proj );
}

void display() {
	float dtime = timer::diff();
	g_time += dtime;
	if( g_time > 1 ) {
		g_time = 0;
		cout << "FPS: " << ( 1.0f/dtime ) << endl;
	}

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
	

	ShaderProgram* sprog = new ShaderProgram();
	sprog->load( GL_VERTEX_SHADER, "basic.vs" ); 
	sprog->load( GL_FRAGMENT_SHADER, "basic.fs", true );
	sprog->use();
	string uniforms[3] = { "m4_projection", "m4_camera", "m4_model" };
	sprog->locate_uniforms( uniforms, 3 );
	sprog->debug();
	manager::shaders::load( sprog );

	Camera camera;
	camera.position( vec3( 0, 1.0f, 3.0f ) );
	camera.apply_transform();
	camera.bind( manager::shaders::uloc( 0, "m4_camera" ) );

	Object* pObj = new Object();
	pObj->load_shape( new Cube( 0.5f ) );
	pObj->mat_model_loc( manager::shaders::uloc( 0, "m4_model" ) );
	pObj->position( vec3( 1, 0, 0 ) );//->velocity( vec3( 0.1f, 0, 0 ) );
	manager::objects::load( pObj );

	Object* pObj2 = new Object();
	pObj2->load_shape( new Cube( 0.1f, vec3( 1, 0, 0 ) ) );
	pObj2->mat_model_loc( manager::shaders::uloc( 0, "m4_model" ) );
	pObj2->position( vec3( -1, 0, 0 ) );//->velocity( vec3( -0.1f, 0, 0 ) );
	manager::objects::load( pObj2 );
	

	// load glut procedures
	glutReshapeFunc( reshape );
	glutDisplayFunc( display );
	glutKeyboardFunc( keyboard );

	// glut main loop
	atexit( quit );
	glutMainLoop();
}
