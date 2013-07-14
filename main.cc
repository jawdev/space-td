#include "config.h"

string SETTINGS::title = "Space TD";
unsigned int SETTINGS::width = 800;
unsigned int SETTINGS::height = 600;
string SETTINGS::path_resources = "resources/";
string SETTINGS::path_shaders = SETTINGS::path_resources+"shaders/";


//---------------------------- variables

enum uniform_t { M4_MODEL, M4_PROJECTION, FLOAT_TMP, TERM };

GLuint vao[1];
GLuint ebo[1];
GLuint vbo[1];
GLint uniforms[TERM];

//---------------------------- helpers

void reshape( int w, int h ) {
	glViewport( 0, 0, w, h );
}

void display( void ) {
	glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
	glDrawElements( GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0 );
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
	if( !Setup::init_glut( &argc, argv ) ) exit( EXIT_FAILURE );
	if( !Setup::create_window( SETTINGS::width, SETTINGS::height, SETTINGS::title.c_str() ) ) exit( EXIT_FAILURE );
	if( !Setup::init_glew() ) exit( EXIT_FAILURE );

	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

	// basic shapes
	GLfloat vertices[3][4] = {
		{ -0.5, -0.5, 0, 1.0f },
		{ 0.0,  0.5, 0, 1.0f },
		{ 0.5,  -0.5, 0, 1.0f },
	};

	GLfloat colors[3][4] = {
		{ 1.0, 0, 0, 1.0 },
		{ 0, 1.0, 0, 1.0 },
 		{ 0, 0, 1.0, 1.0 }
	};

	GLushort indices[3] = {
		0, 2, 1
	};

	glGenBuffers( 1, ebo );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo[0] );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices, GL_STATIC_DRAW );
	
	glGenVertexArrays( 1, vao );
	glBindVertexArray( vao[0] );

	glGenBuffers( 1, vbo );
	glBindBuffer( GL_ARRAY_BUFFER, vbo[0] );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices )+sizeof( colors ), NULL, GL_STATIC_DRAW );
	glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof( vertices ), vertices );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof( vertices ), sizeof( colors ), colors );

	ShaderProgram shaders;
	shaders.load( GL_VERTEX_SHADER, "basic.vs" ); 
	shaders.load( GL_FRAGMENT_SHADER, "basic.fs", true );
	glUseProgram( shaders.program() );
	shaders.debug();
	{ //shader settings
		uniforms[M4_MODEL] = glGetUniformLocation( shaders.program(), "m4_model" );
		uniforms[M4_PROJECTION] = glGetUniformLocation( shaders.program(), "m4_projection" );
		uniforms[FLOAT_TMP] = glGetUniformLocation( shaders.program(), "f_tmp" );

		vmath::mat4 model = vmath::translate( 0.0f, 0.0f, -1.0f );
		glUniformMatrix4fv( uniforms[M4_MODEL], 1, GL_FALSE, model );

		float aspect = (float)SETTINGS::width/(float)SETTINGS::height;
		vmath::mat4 proj = vmath::frustum( -1, 1, -aspect, aspect, 1, 500 );
		glUniformMatrix4fv( uniforms[M4_PROJECTION], 1, GL_FALSE, proj );
	}

	glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 0, NULL );
	glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, 0, (const void*)sizeof( vertices ) );
	glEnableVertexAttribArray( 0 );
	glEnableVertexAttribArray( 1 );

	glBindVertexArray( vao[0] );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo[0] );

	// load glut procedures
	glutReshapeFunc( reshape );
	glutDisplayFunc( display );
	glutKeyboardFunc( keyboard );
	glutMainLoop();
}
