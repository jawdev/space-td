#include "config.h"

///////////////////////////////////////////////// Shader

Shader::Shader( string path, GLenum type, bool run_compile ) {
	m_path = path;
	m_type = type;
	if( run_compile ) compile();
}

Shader::~Shader() {
}

bool Shader::compile() {
	m_shaderID = glCreateShader( m_type );
	const char* source = tools::file_get_contents( ( SETTINGS::path_shaders+m_path ).c_str(), true );
	glShaderSource( m_shaderID, 1, &source, NULL );
	glCompileShader( m_shaderID );
	GLint compiled;
	glGetShaderiv( m_shaderID, GL_COMPILE_STATUS, &compiled );
	if( !compiled ) {
		GLsizei len;
		glGetShaderiv( m_shaderID, GL_INFO_LOG_LENGTH, &len );
		GLchar* log = new GLchar[len+1];
		glGetShaderInfoLog( m_shaderID, len, &len, log );
		cerr << "Shader::load> Could not compile shader: " << log << endl;
		delete [] log;
		return false;
	}
	return true;
}

//----------------- get

GLuint Shader::id() { return m_shaderID; }
string Shader::path() { return m_path; }
GLenum Shader::type() { return m_type; }
