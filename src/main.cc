#include "config.h"

string SETTINGS::title = "Space TD";
unsigned int SETTINGS::width = 800;
unsigned int SETTINGS::height = 600;
string SETTINGS::path_resources = "resources/";
string SETTINGS::path_shaders = SETTINGS::path_resources+"shaders/";

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

	// update
	manager::objects::update( 0, dtime );

	// render
	manager::objects::bind( 0 );
	glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
	manager::objects::render( 0 );

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
}

//---------------------------- init

int main( int argc, char* argv[] ) {
	if( !Setup::init_glut( &argc, argv ) ) exit( EXIT_FAILURE );
	if( !Setup::create_window( SETTINGS::width, SETTINGS::height, SETTINGS::title.c_str() ) ) exit( EXIT_FAILURE );
	if( !Setup::init_glew() ) exit( EXIT_FAILURE );
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

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
	manager::objects::load( pObj );

	// load glut procedures
	glutReshapeFunc( reshape );
	glutDisplayFunc( display );
	glutKeyboardFunc( keyboard );

	// glut main loop
	atexit( quit );
	glutMainLoop();
}
