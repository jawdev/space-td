#include "config.h"

bool SETTINGS::debug = false;
string SETTINGS::title = "Space TD";
unsigned int SETTINGS::width = 800;
unsigned int SETTINGS::height = 600;
string SETTINGS::path_resources = "resources/";
string SETTINGS::path_shaders = SETTINGS::path_resources+"shaders/";


//---------------------------- init

int main( int argc, char* argv[] ) {
	if( !Setup::init_glut( &argc, argv ) ) exit( EXIT_FAILURE );
	if( !Setup::create_window( SETTINGS::width, SETTINGS::height, SETTINGS::title.c_str() ) ) exit( EXIT_FAILURE );
	if( !Setup::init_glew() ) exit( EXIT_FAILURE );

	glClearColor( 0.2f, 0.0f, 0.2f, 1.0f );
	manager::states::load( new TestArea(), "test" );
	manager::states::activate( "test" );

	Setup::default_callbacks();
	Setup::begin_main_loop();
}
