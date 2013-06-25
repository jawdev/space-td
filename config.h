#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <fstream>
#include <iostream>
#include <string>
#include <cstring>

#ifdef __APPLE__ //mac includes
	#include <OpenGL/glu.h>
	#include <OpenGL/glext.h>
	#include <GLUT/glut.h>
#else //everything else	
	#include <GL/glew.h>
	#include <GL/freeglut.h>
	#include <GL/glu.h>
#endif

using namespace std;


 // Global objects
namespace GLOBAL {

}

 // Global settings
namespace SETTINGS {
	string title = "Space TD";
	unsigned int width = 800;
	unsigned int height = 600;
	
}


#endif
