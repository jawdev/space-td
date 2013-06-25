#ifndef __SHADER_H__
#define __SHADER_H__


///////////////////////////////////////////////// Shader

 /* used as a wrapper for OpenGL shaders */
class Shader {
public:
	Shader( string path, GLenum type, bool run_compile=true );
	~Shader();
	bool compile();

	// get
	GLuint id();
	string path();
	GLenum type();

private:
	GLuint m_shaderID;	//loaded from glCreateShader
	string m_path;		//path to shader file
	GLenum m_type;		//shader type

};


#endif //__SHADER_H_
