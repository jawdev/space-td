#include "config.h"

int main( int argc, char* argv[] ) {

	cout << "Starting SDL..." << endl;
	SDL_Init( SDL_INIT_EVERYTHING );
	
	cout << "Quitting SDL..." << endl;
	SDL_Quit();

	
	return 0;
}
