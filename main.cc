#include "config.h"

string SETTINGS::title = "Space TD";
unsigned int SETTINGS::width = 200;
unsigned int SETTINGS::height = 200;
string SETTINGS::path_resources = "resources/";
string SETTINGS::path_shaders = SETTINGS::path_resources+"shaders/";


//---------------------------- variables

enum uniform_t { M4_MODEL, M4_PROJECTION, FLOAT_TMP, TERM };

GLuint vao[1];
GLuint ebo[1];
GLuint vbo[1];
GLint uniforms[TERM];
float change = 0;

//---------------------------- helpers

void reshape( int w, int h ) {
	glViewport( 0, 0, w, h );
}

void display() {
	vmath::mat4 model( vmath::translate( 0.0f, 0.0f, -2.0f )*vmath::rotate( change, Y ) );
	glUniformMatrix4fv( uniforms[M4_MODEL], 1, GL_FALSE, model );
	change += 0.001f;

	glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
	glDrawElements( GL_TRIANGLE_STRIP, 17, GL_UNSIGNED_SHORT, 0 );

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
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

	glEnable( GL_CULL_FACE );
	glEnable( GL_PRIMITIVE_RESTART );

	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

	// basic shapes
	GLfloat vertices[8][4] = {
		{  0.5,  0.5,  0.5, 1 }, //0: front top right
		{  0.5, -0.5,  0.5, 1 }, //1: front bottom right
		{ -0.5, -0.5,  0.5, 1 }, //2: front bottom left
		{ -0.5,  0.5,  0.5, 1 }, //3: front top left
		{  0.5,  0.5, -0.5, 1 }, //4: back top right
		{  0.5, -0.5, -0.5, 1 }, //5: back bottom right
		{ -0.5, -0.5, -0.5, 1 }, //6: back bottom left
		{ -0.5,  0.5, -0.5, 1 }, //7: back top left
	};

	GLfloat colors[8][4] = {
		{ 0, 0, 0, 1 },
		{ 0, 0, 1, 1 },
		{ 0, 1, 0, 1 },
 		{ 0, 1, 1, 1 },
		{ 1, 0, 0, 1 },
		{ 1, 0, 1, 1 },
 		{ 1, 1, 0, 1 },
 		{ 1, 1, 1, 1 }
	};

	GLushort indices[17] = {
		5, 6, 4, 7, 0, 3, 1, 2,
		0xff,
		3, 7, 2, 6, 1, 5, 0, 4
	};
	glPrimitiveRestartIndex( 0xff );

	glGenBuffers( 1, ebo );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo[0] );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices, GL_DYNAMIC_DRAW );
	
	glGenVertexArrays( 1, vao );
	glBindVertexArray( vao[0] );

	glGenBuffers( 1, vbo );
	glBindBuffer( GL_ARRAY_BUFFER, vbo[0] );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices )+sizeof( colors ), NULL, GL_DYNAMIC_DRAW );
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

		float aspect = (float)SETTINGS::height/(float)SETTINGS::width;
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
