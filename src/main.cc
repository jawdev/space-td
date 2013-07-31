#include "config.h"

bool SETTINGS::debug = true;
string SETTINGS::title = "Space TD";
unsigned int SETTINGS::width = 800;
unsigned int SETTINGS::height = 600;
string SETTINGS::path_resources = "resources/";
string SETTINGS::path_shaders = SETTINGS::path_resources+"shaders/";

//---------------------------- TEMPORARY

State* g_state;

//---------------------------- helpers

void reshape( int w, int h ) {
	glViewport( 0, 0, w, h );
	SETTINGS::width = w;
	SETTINGS::height = h;

	// update projection
	g_state->reshape();
}

void display() {

	g_state->display();
	
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
	delete g_state;
}


//---------------------------- init

int main( int argc, char* argv[] ) {
	if( !Setup::init_glut( &argc, argv ) ) exit( EXIT_FAILURE );
	if( !Setup::create_window( SETTINGS::width, SETTINGS::height, SETTINGS::title.c_str() ) ) exit( EXIT_FAILURE );
	if( !Setup::init_glew() ) exit( EXIT_FAILURE );
	glClearColor( 0.2f, 0.0f, 0.2f, 1.0f );

	g_state = new TestArea();
	g_state->load();

	// load glut procedures
	glutReshapeFunc( reshape );
	glutDisplayFunc( display );
	glutKeyboardFunc( keyboard );

	// glut main loop
	atexit( quit );
	glutMainLoop();
}
