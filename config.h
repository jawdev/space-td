#ifndef __CONFIG_H__
#define __CONFIG_H__

// basic system
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

//mac includes
#ifdef __APPLE__ 
	#include <OpenGL/glu.h>
	#include <OpenGL/glext.h>
	#include <GLUT/glut.h>

//everything else	
#else 
	#include <GL/glew.h>
	#include <GL/freeglut.h>
	#include <GL/glu.h>

#endif //__APPLE__

// user files
#include "shader.h"


 /* global objects */
namespace GLOBAL {

}

 /* global settings -- all loaded in main.cc  */
namespace SETTINGS {

	// window
	extern string title;
	extern unsigned int width;
	extern unsigned int height;
	
	// resources
	extern string path_resources;
	extern string path_shaders;
}

 /* Useful functions */
namespace tools {
	
	 /* read file and return char* */
	inline char* file_get_contents( const char* filename, bool zero_term=false ) {
		ifstream in( filename, ios::in|ios::binary );
		if( !in ) {
			cerr << "tools::file_get_contents> File could not be read: " << filename << endl;
			exit( 1 );
		}
		char *contents;
		in.seekg( 0, ios::end );
		unsigned int len = (unsigned int)in.tellg();
		contents = new char[len+1];
		in.seekg( 0, ios::beg );
		in.read( contents, len );
		in.close();
		contents[len] = 0;
		return contents;
	}
}

#endif //__CONFIG_H__
