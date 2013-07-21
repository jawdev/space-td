#include "config.h"


string SETTINGS::title = "Space TD";
unsigned int SETTINGS::width = 800;
unsigned int SETTINGS::height = 600;
string SETTINGS::path_resources = "resources/";
string SETTINGS::path_shaders = SETTINGS::path_resources+"shaders/";


//---------------------------- variables

float change = 0;
Object* pObj;

//---------------------------- helpers

void reshape( int w, int h ) {
	glViewport( 0, 0, w, h );
	SETTINGS::width = w;
	SETTINGS::height = h;

	// update projection
	float aspect = (float)SETTINGS::height/(float)SETTINGS::width;
	vmath::mat4 proj = vmath::frustum( -1, 1, -aspect, aspect, 1, 500 );
	glUniformMatrix4fv( GLOBAL::shaderPrograms.get( 0 )->uloc( "m4_projection" ), 1, GL_FALSE, proj );
}

void display() {
	float dtime = timer::diff();

	pObj->update( dtime );

	pObj->bind();
	glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
	pObj->render();

	//glFlush();
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

	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	pObj = new Object();
	pObj->load_shape( new Cube( 0.5f ) );
	pObj->velocity( vec3( 1.0f, 0, 0 ) );

	ShaderProgram* shaders = new ShaderProgram();
	shaders->load( GL_VERTEX_SHADER, "basic.vs" ); 
	shaders->load( GL_FRAGMENT_SHADER, "basic.fs", true );
	glUseProgram( shaders->program() );
	string uniforms[3] = { "m4_projection", "m4_camera", "m4_model" };
	shaders->locate_uniforms( uniforms, 3 );
	shaders->debug();
	GLOBAL::shaderPrograms.load( shaders );

	GLOBAL::camera.position( vec3( 0, 1.0f, 3.0f ) );
	GLOBAL::camera.apply_transform();
	GLOBAL::camera.bind( GLOBAL::shaderPrograms.get( 0 )->uloc( "m4_camera" ) );

	// load glut procedures
	glutReshapeFunc( reshape );
	glutDisplayFunc( display );
	glutKeyboardFunc( keyboard );
	glutMainLoop();
}
