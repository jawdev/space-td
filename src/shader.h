#ifndef __SHADER_H__
#define __SHADER_H__
namespace jaw3d {


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


///////////////////////////////////////////////// ShaderProgram

/* Wrapper for OpenGL shader program */
class ShaderProgram {
public:
	ShaderProgram();
	~ShaderProgram();
	bool link();
	void use();
	void debug();

	// load
	Shader* load( GLenum type, string path, bool run_link=false );

	// uniform
	void locate_uniforms( string* labels, unsigned int amt );
	GLint uloc( string lbl );

	// get
	GLuint program();

	// helpers
	unsigned int map( GLenum type );
private:
	static const unsigned int SC = 2;

	GLuint m_program;
	Shader* m_shaders[SC];
	vector< string > m_uniformLbls;
	vector< GLint > m_uniformLocs;
};

}
#endif //__SHADER_H__
