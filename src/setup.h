#ifndef __SETUP_H_
#define __SETUP_H_
namespace jaw3d {

////////////////////////////////////////////////// Setup

/* static functions to setup OpenGL environment */

class Setup {
public:

	// init
	static bool init_glut( int* argc, char* argv[] );
	static bool init_glew();
	static bool init_glut_glew( int* argc, char* argv[] );
	static bool create_window( unsigned int w=800, unsigned int h=600, const char* title=NULL );

	// callbacks
	static bool default_callback_reshape();
	static bool default_callback_display();
	static bool default_callback_keyboard();
	static bool default_callback_mouse();
	static bool default_callback_quit();
	static bool default_callbacks();

	// run
	static void begin_main_loop();
private:
	static void callback_reshape( int w, int h );
	static void callback_display();
	static void callback_keydown( unsigned char key, int x, int y );
	static void callback_keyup( unsigned char key, int x, int y );
	static void callback_specialdown( int k, int x, int y );
	static void callback_specialup( int k, int x, int y );
	static void callback_mouse( int button, int state, int x, int y );
	static void callback_mousemove( int x, int y );
	static void callback_quit();

};

} //jaw3d
#endif //__SETUP_H__
