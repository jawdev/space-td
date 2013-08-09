#include "config.h"
namespace jaw3d {

////////////////////////////////////////////////// Setup

//----------------- init

bool Setup::init_glut( int* argc, char* argv[] ) {
	glutInit( argc, argv );
	glutInitDisplayMode( GLUT_RGBA );
	glutInitContextVersion( 4, 3 );
	glutInitContextProfile( GLUT_CORE_PROFILE );
	return true;
}

bool Setup::init_glew() {
	glewExperimental = GL_TRUE;
	if( glewInit() ) {
		cerr << "Setup::init_glew> unable to initialize GLEW" << endl;
		return false;
	}
	return true;
}

bool Setup::create_window( unsigned int w, unsigned int h, const char* title ) {
	if( title == NULL ) title = GLOBAL::TITLE.c_str();
	glutInitWindowSize( w, h );
	glutCreateWindow( title );
	return true;
}

//----------------- callbacks

bool Setup::default_callback_reshape() {
	glutReshapeFunc( Setup::callback_reshape );
	return true;
}

bool Setup::default_callback_display() {
	glutDisplayFunc( Setup::callback_display );
	return true;
}

bool Setup::default_callback_keyboard() {
	glutKeyboardFunc( Setup::callback_keydown );
	return true;
}

bool Setup::default_callback_mouse() {
	glutMouseFunc( Setup::callback_mouse );
	return true;
}

bool Setup::default_callback_quit() {
	atexit( Setup::callback_quit );
	return true;
}

bool Setup::default_callbacks() {
	return ( default_callback_reshape() && default_callback_display() && default_callback_keyboard() && default_callback_mouse() && default_callback_quit() );
}

void Setup::callback_reshape( int w, int h ) {
	glViewport( 0, 0, w, h );
	SETTINGS::width = w;
	SETTINGS::height = h;
	manager::states::reshape();
}

void Setup::callback_display() {
	manager::states::display();
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void Setup::callback_keydown( unsigned char key, int x, int y ) {
	switch( key ) {
	case 27:
		exit( 0 );
		break;
	}
	manager::states::key( key, true );
}

void Setup::callback_mouse( int button, int state, int x, int y ) {

}

void Setup::callback_quit() {
	manager::release_all();
}

//----------------- run

void Setup::begin_main_loop() {
	glutMainLoop();
}

} //jaw3d
