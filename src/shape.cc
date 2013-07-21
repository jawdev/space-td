#include "config.h"

///////////////////////////////////////////////// Shape

Shape::Shape( shape_draw_t drawType ) {
	m_drawType = drawType;
	glGenVertexArrays( 1, &m_va );
	if( drawType == shape_draw_t::LIST ) {
	} else if( drawType == shape_draw_t::INDEX ) {
		glGenBuffers( 1, &m_vb );
		glGenBuffers( 1, &m_eb );
	}
}

Shape::~Shape() {

}

//----------------- update


///////////////////////////////////////////////// Cube

Cube::Cube( float radius ) : Shape( shape_draw_t::INDEX ) {
	m_radius = radius;

	// vertices
	m_vertices = new GLfloat[CV];
	GLfloat temp_v[CV] = {
		 radius,  radius,  radius, 1, //0: front top right
		 radius, -radius,  radius, 1, //1: front bottom right
		-radius, -radius,  radius, 1, //2: front bottom left
		-radius,  radius,  radius, 1, //3: front top left
		 radius,  radius, -radius, 1, //4: back top right
		 radius, -radius, -radius, 1, //5: back bottom right
		-radius, -radius, -radius, 1, //6: back bottom left
		-radius,  radius, -radius, 1 //7: back top left
	};
	for( unsigned int i = 0; i < CV; i++ ) m_vertices[i] = temp_v[i];

	m_colors = new GLfloat[CV];
	GLfloat temp_c[CV] = {
		1, 0, 0, 1,
		0, 0, 1, 1,
		0, 0, 1, 1,
		1, 0, 0, 1,
		1, 0, 0, 1,
		0, 0, 1, 1,
		0, 0, 1, 1,
		1, 0, 0, 1
	};
	for( unsigned int i = 0; i < CV; i++ ) m_colors[i] = temp_c[i];

	// indices
	m_indices = new GLushort[CI];
	GLushort temp_i[CI] = {
		5, 6, 4, 7, 0, 3, 1, 2,
		0xff,
		3, 7, 2, 6, 1, 5, 0, 4
	};
	for( unsigned int i = 0; i < CI; i++ ) m_indices[i] = temp_i[i];
	
}

Cube::~Cube() {
	delete m_indices;
	delete m_colors;
	delete m_vertices;
}

//----------------- update

void Cube::bind() {
	glEnable( GL_CULL_FACE );
	glEnable( GL_PRIMITIVE_RESTART );
	glPrimitiveRestartIndex( 0xff );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_eb );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, CI*sizeof( GLushort ), m_indices, GL_STATIC_DRAW );

	glBindVertexArray( m_va );

	glBindBuffer( GL_ARRAY_BUFFER, m_vb );
	glBufferData( GL_ARRAY_BUFFER, 2*CV*sizeof( GLfloat ), NULL, GL_STATIC_DRAW );
	glBufferSubData( GL_ARRAY_BUFFER, 0, CV*sizeof( GLfloat ), m_vertices );
	glBufferSubData( GL_ARRAY_BUFFER, CV*sizeof( GLfloat ), CV*sizeof( GLfloat ), m_colors );

	glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 0, NULL );
	glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, 0, (const void*)( CV*sizeof( GLfloat ) ) );
	glEnableVertexAttribArray( 0 );
	glEnableVertexAttribArray( 1 );

	glBindVertexArray( m_va );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_eb );
}

void Cube::render() {
	glDrawElements( GL_TRIANGLE_STRIP, CI, GL_UNSIGNED_SHORT, 0 );
}

//----------------- get

float Cube::radius() { return m_radius; }
