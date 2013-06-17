#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_opengl.h>

#ifdef __APPLE__ //mac includes
	#include <OpenGL/glu.h>
	#include <OpenGL/glext.h>
#else //everything else	
#endif

using namespace std;


 // Global objects
namespace GLOBAL {

	SDL_Window* window = NULL;
	SDL_GLContext ctx;

}

 // Global settings
namespace SETTINGS {
	string title = "Space TD";
	unsigned int width = 800;
	unsigned int height = 600;
	
}


#endif
