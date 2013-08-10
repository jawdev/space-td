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
	glutIgnoreKeyRepeat( 1 );
	glutKeyboardFunc( Setup::callback_keydown );
	glutSpecialFunc( Setup::callback_specialdown );
	glutKeyboardUpFunc( Setup::callback_keyup );
	glutSpecialUpFunc( Setup::callback_specialup );
	return true;
}

bool Setup::default_callback_mouse() {
	glutSetCursor( GLUT_CURSOR_NONE );
	glutMouseFunc( Setup::callback_mouse );
	glutPassiveMotionFunc( Setup::callback_mousemove );
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
	manager::states::new_key_event( (unsigned int)key, key_event_t::DOWN );
}

void Setup::callback_keyup( unsigned char key, int x, int y ) {
	manager::states::new_key_event( (unsigned int)key, key_event_t::UP );
}

void Setup::callback_specialdown( int k, int x, int y ) {
	unsigned int key = (unsigned int)( k + 100 );
	manager::states::new_key_event( key, key_event_t::DOWN );
}

void Setup::callback_specialup( int k, int x, int y ) {
	unsigned int key = (unsigned int)( k + 100 );
	manager::states::new_key_event( key, key_event_t::UP );
}

void Setup::callback_mouse( int button, int state, int x, int y ) {
	mouse_button_t btn;
	switch( button ) {
		case GLUT_LEFT_BUTTON: btn = mouse_button_t::LEFT; break;
		case GLUT_MIDDLE_BUTTON: btn = mouse_button_t::MIDDLE; break;
		case GLUT_RIGHT_BUTTON: btn = mouse_button_t::RIGHT; break;
		default: btn = mouse_button_t::NONE;
	}
	mouse_event_t e;
	switch( state ) {
		case GLUT_DOWN: e = mouse_event_t::DOWN;
		case GLUT_UP: e = mouse_event_t::UP;
		default: e = mouse_event_t::NONE;
	}
	manager::states::new_mouse_event( btn, e, (unsigned int)x, (unsigned int)y );
}

void Setup::callback_mousemove( int x, int y ) {
	manager::states::new_mouse_event( mouse_button_t::NONE, mouse_event_t::MOVE, (unsigned int)x, (unsigned int)y );
}

void Setup::callback_quit() {
	manager::release_all();
}

//----------------- run

void Setup::begin_main_loop() {
	glutMainLoop();
}

} //jaw3d
