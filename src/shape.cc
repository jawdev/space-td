#include "config.h"
namespace jaw3d {

///////////////////////////////////////////////// Shape

Shape::Shape( vec4 color ) {
	shape_color = color;
}

Shape::~Shape() {}

//----------------- update

//----------------- get

vec4 Shape::color() { return shape_color; }

///////////////////////////////////////////////// FloorPlane

FloorPlane::FloorPlane( float width, float length, vec4 color ) : Shape( color ) {
	m_width = width;
	m_length = length;
	glGenVertexArrays( 1, &m_va );
	glGenBuffers( 1, &m_vb );

	m_vertices = new GLfloat[CV];
	float temp_v[] = {
		-m_width, 0, -m_length, 1,	// top
		-m_width, 0,  m_length, 1,
		 m_width, 0, -m_length, 1,
		 m_width, 0, -m_length, 1,	// bottom
		-m_width, 0,  m_length, 1,
		 m_width, 0,  m_length, 1
	};
	for( unsigned int i = 0; i < CV; i++ ) m_vertices[i] = (GLfloat)temp_v[i];

	m_normals = new GLfloat[CN];
	float temp_n[] = {
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		0, 1, 0
	};
	for( unsigned int i = 0; i < CN; i++ ) m_normals[i] = (GLfloat)temp_n[i];

}

FloorPlane::~FloorPlane() {
	delete [] m_vertices;
	delete [] m_normals;
}

//----------------- update

void FloorPlane::bind() {
	glEnable( GL_CULL_FACE );

	glBindVertexArray( m_va );
	glBindBuffer( GL_ARRAY_BUFFER, m_vb );
	glBufferData( GL_ARRAY_BUFFER, ( CV+CN )*sizeof( GLfloat ), NULL, GL_STATIC_DRAW );
	glBufferSubData( GL_ARRAY_BUFFER, 0, CV*sizeof( GLfloat ), m_vertices );
	glBufferSubData( GL_ARRAY_BUFFER, CV*sizeof( GLfloat ), CN*sizeof( GLfloat ), m_normals );

	// position, normal
	glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 0, 0 );
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (const void*)( CV*sizeof( float ) ) );
	glEnableVertexAttribArray( 0 );
	glEnableVertexAttribArray( 1 );

	// color
	vmath::vec4 v( shape_color.x, shape_color.y, shape_color.z, shape_color.w );
	glVertexAttrib4fv( 2, v );

	glBindVertexArray( m_va );
	glBindBuffer( GL_ARRAY_BUFFER, m_vb );
}

void FloorPlane::render() {
	glDrawArrays( GL_TRIANGLES, 0, 6 );
}

//----------------- get

float FloorPlane::width() { return m_width; }
float FloorPlane::length() { return m_length; }

///////////////////////////////////////////////// Cube

Cube::Cube( float radius, vec4 color ) : Shape( color ) {
	m_radius = radius;
	glGenVertexArrays( 1, &m_va );
	glGenBuffers( 1, &m_vb );

	// vertices
	m_vertices = new GLfloat[CV];
	float temp_v[] = {
		-radius,  radius,  radius, 1,	// front top
		-radius, -radius,  radius, 1,
		 radius,  radius,  radius, 1,
		 radius,  radius,  radius, 1,	// front bottom
		-radius, -radius,  radius, 1,
	 	 radius, -radius,  radius, 1,

		 radius,  radius, -radius, 1,	// back top
		-radius, -radius, -radius, 1,
		-radius,  radius, -radius, 1,
		 radius,  radius, -radius, 1,	// back bottom
		 radius, -radius, -radius, 1,
		-radius, -radius, -radius, 1,

		-radius,  radius, -radius, 1,	// left top
		-radius, -radius, -radius, 1,
		-radius,  radius,  radius, 1,
		-radius,  radius,  radius, 1,	// left bottom
		-radius, -radius, -radius, 1,
		-radius, -radius,  radius, 1,

		 radius,  radius,  radius, 1,	// right top
		 radius, -radius, -radius, 1,
		 radius,  radius, -radius, 1,
		 radius, -radius, -radius, 1,	// right bottom
		 radius,  radius,  radius, 1,
		 radius, -radius,  radius, 1,

		-radius,  radius, -radius, 1,	// top top
		-radius,  radius,  radius, 1,
		 radius,  radius, -radius, 1,
		 radius,  radius, -radius, 1,	// top bottom
		-radius,  radius,  radius, 1,
		 radius,  radius,  radius, 1,

		-radius, -radius,  radius, 1,	// bottom top
		-radius, -radius, -radius, 1,
		 radius, -radius,  radius, 1,
		 radius, -radius,  radius, 1,	// bottom bottom
		-radius, -radius, -radius, 1,
		 radius, -radius, -radius, 1
	};
	for( unsigned int i = 0; i < CV; i++ ) m_vertices[i] = (GLfloat)temp_v[i];

	// normals
	m_normals = new GLfloat[CN];
	float temp_n[] = {
		 0,  0,  1,	// front
		 0,  0,  1,
		 0,  0,  1,
		 0,  0,  1,
		 0,  0,  1,
		 0,  0,  1,
		
		 0,  0, -1,	// back
		 0,  0, -1,
		 0,  0, -1,
		 0,  0, -1,
		 0,  0, -1,
		 0,  0, -1,

		-1,  0,  0,	// left
		-1,  0,  0,
		-1,  0,  0,
		-1,  0,  0,
		-1,  0,  0,
		-1,  0,  0,

		 1,  0,  0,	// right
		 1,  0,  0,
		 1,  0,  0,
		 1,  0,  0,
		 1,  0,  0,
		 1,  0,  0,

		 0,  1,  0,	// top
		 0,  1,  0,
		 0,  1,  0,
		 0,  1,  0,
		 0,  1,  0,
		 0,  1,  0,

		 0, -1,  0,	// bottom
		 0, -1,  0,
		 0, -1,  0,
		 0, -1,  0,
		 0, -1,  0,
		 0, -1,  0
	};
	for( unsigned int i = 0; i < CN; i++ ) m_normals[i] = (GLfloat)temp_n[i];
}

Cube::~Cube() {
	delete [] m_vertices;
	delete [] m_normals;
}

//----------------- update

void Cube::bind() {
	glEnable( GL_CULL_FACE );

	glBindVertexArray( m_va );
	glBindBuffer( GL_ARRAY_BUFFER, m_vb );
	glBufferData( GL_ARRAY_BUFFER, ( CV+CN )*sizeof( GLfloat ), NULL, GL_STATIC_DRAW );
	glBufferSubData( GL_ARRAY_BUFFER, 0, CV*sizeof( GLfloat ), m_vertices );
	glBufferSubData( GL_ARRAY_BUFFER, CV*sizeof( GLfloat ), CN*sizeof( GLfloat ), m_normals );

	// position, normal
	glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 0, 0 );
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (const void*)( CV*sizeof( float ) ) );
	glEnableVertexAttribArray( 0 );
	glEnableVertexAttribArray( 1 );

	// color
	vmath::vec4 v( shape_color.x, shape_color.y, shape_color.z, shape_color.w );
	glVertexAttrib4fv( 2, v );

	glBindVertexArray( m_va );
	glBindBuffer( GL_ARRAY_BUFFER, m_vb );
}

void Cube::render() {
	glDrawArrays( GL_TRIANGLES, 0, 36 );
}

//----------------- get

float Cube::radius() { return m_radius; }

}
