#include "config.h"
namespace jaw3d {

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


///////////////////////////////////////////////// ShaderProgram

ShaderProgram::ShaderProgram() {
	for( unsigned int i = 0; i < SC; i++ ) m_shaders[i] = NULL;
	m_program = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
	delete * m_shaders;
	m_uniformLocs.clear();
	m_uniformLbls.clear();
}

bool ShaderProgram::link() {
	glLinkProgram( m_program );
	GLint linked;
	glGetProgramiv( m_program, GL_LINK_STATUS, &linked );
	if( !linked ) {
		GLsizei len;
		glGetProgramiv( m_program, GL_INFO_LOG_LENGTH, &len );
		GLchar* log = new GLchar[len+1];
		glGetProgramInfoLog( m_program, len, &len, log );
		cerr << "ShaderProgram::link> shader linking failed: " << log << endl;
		delete [] log;
		return false;
	}
	return true;
}

void ShaderProgram::use() {
	glUseProgram( m_program );
}

void ShaderProgram::debug() {
	cout << "Debugging GLSL program..." << endl;

	// check if program exists
	if( !glIsProgram( m_program ) ) {
		cout << "  [FAIL] program does not exist, ID=" << m_program << endl;
		exit( EXIT_FAILURE );
	} else cout << "  [OK] program exists, ID=" << m_program << endl;

	// make sure program is valid
	GLint program_valid = 0;
	glValidateProgram( m_program );
	glGetProgramiv( m_program, GL_VALIDATE_STATUS, &program_valid );
	if( !program_valid ) {
		cout << "  [FAIL] program validation failed" << endl;
		exit( EXIT_FAILURE );
	} else cout << "  [OK] program validated" << endl;
	
	// make sure program is active program
	GLint current_program = 0;
	glGetIntegerv( GL_CURRENT_PROGRAM, &current_program );
	if( current_program == 0 ) {
		cout << "  [WARN] Current program not active program" << endl;
	} else cout << "  [OK] program is active" << endl;

	GLint num_uniforms = 0;
	glGetProgramiv( m_program, GL_ACTIVE_UNIFORMS, &num_uniforms );
	cout << "  [INFO] " << num_uniforms << " active uniforms." << endl;
 
	cout << "  [INFO] " << m_uniformLocs.size() << " located uniforms." << endl;
	for( unsigned int i = 0; i < m_uniformLocs.size(); i++ ) {
		cout << "    {" << m_uniformLocs[i] << ",";
		cout << m_uniformLbls[i] << "}" << endl;
	}
	cout << "debug complete" << endl;
}

//----------------- load

Shader* ShaderProgram::load( GLenum type, string path, bool run_link ) {
	unsigned int id = map( type );
	m_shaders[id] = new Shader( path, type, false );
	if( !m_shaders[id]->compile() ) exit( EXIT_FAILURE );
	glAttachShader( m_program, m_shaders[id]->id() );
	if( run_link && !link() ) exit( EXIT_FAILURE );
	return m_shaders[id];
}

//----------------- uniform

void ShaderProgram::locate_uniforms( string* labels, unsigned int amt ) {
	for( unsigned int i = 0; i < amt; i++ ) {
		m_uniformLbls.push_back( labels[i] );
		m_uniformLocs.push_back( glGetUniformLocation( m_program, labels[i].c_str() ) );
	}
}

GLint ShaderProgram::uloc( string label ) {
	for( unsigned int i = 0; i < m_uniformLbls.size(); i++ ) {
		if( m_uniformLbls[i].compare( label ) == 0 ) {
			return m_uniformLocs[i];
		}
	}
	return -1;
}

//----------------- get

GLuint ShaderProgram::program() { return m_program; }

//----------------- helper functions

 /* associates a shader type with an array index */
unsigned int ShaderProgram::map( GLenum type ) {
	switch( type ) {
		case GL_VERTEX_SHADER: return 0;
		case GL_FRAGMENT_SHADER: return 1;
		default: return 666;
	}
}

}
