#include "config.h"

void display( void ) {
	glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
	glutSwapBuffers();

}


void menu_select( int v ) {
	exit( 0 );
}


int main( int argc, char* argv[] ) {

	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA );
	glutInitWindowSize( SETTINGS::width, SETTINGS::height );
	glutCreateWindow( SETTINGS::title.c_str() );

	glutCreateMenu( menu_select );
	glutAddMenuEntry( "Exit", 0 );
	glutAttachMenu( GLUT_RIGHT_BUTTON );

	glutDisplayFunc( display );
	glutMainLoop();
	
	return 0;
}
