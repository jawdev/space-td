#include "config.h"

//---------------------------- variables

GLuint g_vaos[1];
GLuint g_buffers[1];

//---------------------------- helpers

char* file_get_contents( const char* filename, bool zero_term=false ) {
	ifstream in( filename, ios::in|ios::binary );
	if( !in ) {
		cerr << "File could not be read: " << filename << endl;
		exit( 1 );
	}

	char *contents;
	in.seekg( 0, ios::end );
	unsigned int len = (unsigned int)in.tellg();
	contents = new char[len+1];
	in.seekg( 0, ios::beg );
	in.read( contents, len );
	in.close();
	contents[len] = 0;
	return contents;
}

void reshape( int w, int h ) {
	glViewport( 0, 0, (GLsizei)w, (GLsizei)h );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	float r = (float)w/(float)h;
	glFrustum( -r, r, -1, 1, 1, 10 );
	glMatrixMode( GL_MODELVIEW );
}

void display( void ) {
	glClear( GL_COLOR_BUFFER_BIT );
	glBindVertexArray( g_vaos[0] );
	glDrawArrays( GL_TRIANGLES, 0, 3 );
	glFlush();
}

void keyboard( unsigned char key, int x, int y ) {
	switch( key ) {
	case 27:
		exit( 0 );
		break;
	}
}


//---------------------------- init

int main( int argc, char* argv[] ) {

	// init glut facilities
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA );
	glutInitContextVersion( 4, 3 );
	glutInitContextProfile( GLUT_CORE_PROFILE );

	// create window
	glutInitWindowSize( SETTINGS::width, SETTINGS::height );
	glutCreateWindow( SETTINGS::title.c_str() );

	// init GLEW
	glewExperimental = GL_TRUE;	
	if( glewInit() ) {
		cerr << "Unable to initialize GLEW ... exiting" << endl;
		exit( EXIT_FAILURE );
	}

	// basic shapes
	glGenVertexArrays( 1, g_vaos );
	glBindVertexArray( g_vaos[0] );
	GLfloat vertices[3][2] = {
		{ -1, -1 },
		{ 1, -1 },
		{ -1, 1 }
	};
	glGenBuffers( 1, g_buffers );
	glBindBuffer( GL_ARRAY_BUFFER, g_buffers[0] );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

	// create shaders
	GLuint vshader = glCreateShader( GL_VERTEX_SHADER );
	const char* source1 = file_get_contents( "triangles.vert", true );
	glShaderSource( vshader, 1, &source1, NULL );
	glCompileShader( vshader );
	GLint compiled;
	glGetShaderiv( vshader, GL_COMPILE_STATUS, &compiled );
	if( !compiled ) {
		GLsizei len;
		glGetShaderiv( vshader, GL_INFO_LOG_LENGTH, &len );
		GLchar* log = new GLchar[len+1];
		glGetShaderInfoLog( vshader, len, &len, log );
		cerr << "Vertex shader compilation failed: " << log << endl;
		delete [] log;
		return 1;
	}
	GLuint fshader = glCreateShader( GL_FRAGMENT_SHADER );
	const char* source2 = file_get_contents( "triangles.frag", true );
	glShaderSource( fshader, 1, &source2, NULL );
	glCompileShader( fshader );
	glGetShaderiv( fshader, GL_COMPILE_STATUS, &compiled );
	if( !compiled ) {
		GLsizei len;
		glGetShaderiv( fshader, GL_INFO_LOG_LENGTH, &len );
		GLchar* log = new GLchar[len+1];
		glGetShaderInfoLog( fshader, len, &len, log );
		cerr << "Fragment shader compilation failed: " << log << endl;
		delete [] log;
		return 1;
	}

	// link shaders
	GLuint program = glCreateProgram();
	glAttachShader( program, vshader );
	glAttachShader( program, fshader );
	glLinkProgram( program );
	GLint linked;
	glGetProgramiv( program, GL_LINK_STATUS, &linked );
	if( !linked ) {
		GLsizei len;
		glGetProgramiv( program, GL_INFO_LOG_LENGTH, &len );
		GLchar* log = new GLchar[len+1];
		glGetProgramInfoLog( program, len, &len, log );
		cerr << "Shader linking failed: " << log << endl;
		delete [] log;
		return 1;
	}
	
	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, NULL );
	glEnableVertexAttribArray( 0 );
	

	// load glut procedures
	glutDisplayFunc( display );
	//glutReshapeFunc( reshape );
	glutKeyboardFunc( keyboard );
	glutMainLoop();
}
