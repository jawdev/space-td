#include "config.h"

string SETTINGS::title = "Space TD";
unsigned int SETTINGS::width = 800;
unsigned int SETTINGS::height = 600;
string SETTINGS::path_resources = "resources/";
string SETTINGS::path_shaders = SETTINGS::path_resources+"shaders/";


//---------------------------- variables

GLuint g_vaos[1];
GLuint g_buffers[1];

//---------------------------- helpers

void display( void ) {
	glClear( GL_COLOR_BUFFER_BIT );
	glBindVertexArray( g_vaos[0] );
	glDrawArrays( GL_TRIANGLE_STRIP, 0, 3 );
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
		{ -0.9, 0.9 },
		{ 0.9, 0.9 },
		{ 0.9, -0.9 },
	};
	glGenBuffers( 1, g_buffers );
	glBindBuffer( GL_ARRAY_BUFFER, g_buffers[0] );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

	// create shaders
	Shader vs( "triangles.vert", GL_VERTEX_SHADER );
	Shader fs( "triangles.frag", GL_FRAGMENT_SHADER );

	// link shaders
	GLuint program = glCreateProgram();
	glAttachShader( program, vs.id() );
	glAttachShader( program, fs.id()  );
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
	
	// apply shader info
	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, NULL );
	glEnableVertexAttribArray( 0 );
	

	// load glut procedures
	glutDisplayFunc( display );
	glutKeyboardFunc( keyboard );
	glutMainLoop();
}
