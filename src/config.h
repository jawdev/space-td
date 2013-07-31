#ifndef __CONFIG_H_
#define __CONFIG_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
using namespace std;

#ifdef __APPLE__
	#include <OpenGL/glu.h>
	#include <OpenGL/glext.h>
	#include <GLUT/glut.h>
#else
	#include <GL/glew.h>
	#include <GL/freeglut.h>
	#include <GL/glu.h>

#endif //__APPLE__

// user files
#include "utils.h"
#include "geometry.h"
#include "display.h"
#include "oglpg_vmath.h"
#include "light.h"
#include "camera.h"
#include "shader.h"
#include "shape.h"
#include "object.h"
#include "manager.h"
#include "buffer.h"
#include "state.h"
using namespace jaw3d;

namespace jaw3d {

#define PI (float)M_PI
#define X vmath::vec3( 1.0f, 0.0f, 0.0f )
#define Y vmath::vec3( 0.0f, 1.0f, 0.0f )
#define Z vmath::vec3( 0.0f, 0.0f, 1.0f )

 /* global objects */
namespace GLOBAL {
	// loaded from display.cc

	static const string TITLE = "JAW Development, LLC - 3D OpenGL Wrappers"; 
	static const string VERSION = "0.0";
}

 /* global settings -- all loaded in main.cc  */
namespace SETTINGS {
	extern bool debug;

	// window
	extern string title;
	extern unsigned int width;
	extern unsigned int height;
	
	// resources
	extern string path_resources;
	extern string path_shaders;
}

}
#endif //__CONFIG_H__
