#include "config.h"

void reshape( int w, int h ) {
	glViewport( 0, 0, (GLsizei)w, (GLsizei)h );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	float r = (float)w/(float)h;
	glFrustum( -r, r, -1, 1, 1, 10 );
	glMatrixMode( GL_MODELVIEW );
}

void display( void ) {
	glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
	glColor3f( 1, 1, 1 );
	glLoadIdentity();
	gluLookAt( 0, 0, 2, 0, 0, 0, 0, 1, 0 );
	glutWireCube( 1 );
	glFlush();
}

void keyboard( unsigned char key, int x, int y ) {
	switch( key ) {
	case 27:
		exit( 0 );
		break;
	}
}


int main( int argc, char* argv[] ) {

	// init glut facilities
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA );
	glutInitContextVersion( 3, 3 );
	glutInitContextProfile( GLUT_COMPATIBILITY_PROFILE  );
	glutInitContextFlags( GLUT_FORWARD_COMPATIBLE );

	// create window
	glutInitWindowSize( SETTINGS::width, SETTINGS::height );
	glutCreateWindow( SETTINGS::title.c_str() );

	// redering settings
	glClearColor( 0, 0, 0, 0 );
	glShadeModel( GL_FLAT );

	// load glut procedures
	glutDisplayFunc( display );
	glutReshapeFunc( reshape );
	glutKeyboardFunc( keyboard );
	glutMainLoop();

	// quit normally
	return 0;
}
