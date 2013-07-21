#include "config.h"
namespace jaw3d {

////////////////////////////////////////////////// Setup

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

}
