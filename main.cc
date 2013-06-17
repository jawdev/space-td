#include "config.h"

 // setup sdl
bool setup_sdl() {
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
		cout << "[ERROR] SDL_Init failed: " << SDL_GetError() << endl;
		return false;
	}
	GLOBAL::window = SDL_CreateWindow( SETTINGS::title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SETTINGS::width, SETTINGS::height, SDL_WINDOW_OPENGL );
	if( GLOBAL::window == NULL ) {
		cout << "[ERROR] SDL_CreateWindow failed: " << SDL_GetError() << endl;
		return false;
	}

	return true;
}

bool setup_opengl() {
	GLOBAL::ctx = SDL_GL_CreateContext( GLOBAL::window );
	glMatrixMode( GL_PROJECTION|GL_MODELVIEW );
	glLoadIdentity();
	//glOrtho( -SETTINGS::width/2, SETTINGS::width/2, SETTINGS::height/2, -SETTINGS::height/2, 0, 1 );
	return true;
}

int main( int argc, char* argv[] ) {
	// init
	if( !setup_sdl() ) return 1;
	if( !setup_opengl() ) return 1;

	SDL_Event event;
	bool done = false;
	while( !done ) {
		while( SDL_PollEvent( &event ) ) {
			if( event.type == SDL_QUIT ) done = true;
		}

		// draw
		glClearColor( 0, 0, 0, 1 );
		glClear( GL_COLOR_BUFFER_BIT );

		glBegin( GL_TRIANGLES );
			glColor3f( 1, 0, 0 ); glVertex3f( 0, 1, 0 );
			glColor3f( 0, 1, 0 ); glVertex3f( -1, -1, 0 );
			glColor3f( 0, 0, 1 ); glVertex3f( 1, -1, 0 );
		glEnd();

		SDL_GL_SwapWindow( GLOBAL::window );
		SDL_Delay( 10 );
	}

	// clean up
	SDL_GL_DeleteContext( GLOBAL::ctx );
	SDL_DestroyWindow( GLOBAL::window );
	SDL_Quit();
	return 0;
}
