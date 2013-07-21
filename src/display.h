#ifndef __SETUP_H_
#define __SETUP_H_
namespace jaw3d {

////////////////////////////////////////////////// Setup

/* static functions to setup OpenGL environment */

class Setup {
public:

	static bool init_glut( int* argc, char* argv[] );
	static bool init_glew();
	static bool init_glut_glew( int* argc, char* argv[] );
	static bool create_window( unsigned int w=800, unsigned int h=600, const char* title=NULL );

};

}
#endif
