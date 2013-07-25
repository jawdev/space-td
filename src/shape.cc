#include "config.h"
namespace jaw3d {

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

///////////////////////////////////////////////// Line

Line::Line( vec3 p1, vec3 p2, vec3 color ) : Shape( shape_draw_t::LIST ) {
	m_p1 = p1;
	m_p2 = p2;
	m_color = color;

	m_vertices = new GLfloat[8];
	m_vertices[0] = p1.x;
	m_vertices[1] = p1.y;
	m_vertices[2] = p1.z;
	m_vertices[3] = 1.0f;
	m_vertices[4] = p2.x;
	m_vertices[5] = p2.y;
	m_vertices[6] = p2.z;
	m_vertices[7] = 1.0f;

	m_colors = new GLfloat[8];
	m_colors[0] = m_color.x;
	m_colors[1] = m_color.y;
	m_colors[2] = m_color.z;
	m_colors[3] = 1.0f;
	m_colors[4] = m_color.x;
	m_colors[5] = m_color.y;
	m_colors[6] = m_color.z;
	m_colors[7] = 1.0f;
};

Line::~Line() {
	delete m_colors;
	delete m_vertices;
}

//----------------- update

void Line::bind() {
	glDisable( GL_CULL_FACE );
	glDisable( GL_PRIMITIVE_RESTART );
	glLineWidth( 10.0f );

	glBindVertexArray( m_va );
	glBindBuffer( GL_ARRAY_BUFFER, m_vb );
	glBufferData( GL_ARRAY_BUFFER, 16*sizeof( GLfloat ), NULL, GL_STATIC_DRAW );
	glBufferSubData( GL_ARRAY_BUFFER, 0, 8*sizeof( GLfloat ), m_vertices );
	glBufferSubData( GL_ARRAY_BUFFER, 8*sizeof( GLfloat ), 8*sizeof( GLfloat ), m_colors );
	glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 0, NULL );
	glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, 0, (const void*)( 8*sizeof( GLfloat ) ) );
	glBindVertexArray( m_va );
	glBindBuffer( GL_ARRAY_BUFFER, m_vb );
}

void Line::render() {
	glDrawArrays( GL_LINES, 0, 8 );
}

//----------------- get

vec3 Line::p1() { return m_p1; }
vec3 Line::p2() { return m_p2; }
vec3 Line::color() { return m_color; }

///////////////////////////////////////////////// Cube

Cube::Cube( float radius, vec3 color ) : Shape( shape_draw_t::INDEX) {
	m_radius = radius;
	m_color = color;

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
		m_color.x, m_color.y, m_color.z, 1,
		m_color.x, m_color.y, m_color.z, 1,
		m_color.x, m_color.y, m_color.z, 1,
		m_color.x, m_color.y, m_color.z, 1,
		m_color.x, m_color.y, m_color.z, 1,
		m_color.x, m_color.y, m_color.z, 1,
		m_color.x, m_color.y, m_color.z, 1,
		m_color.x, m_color.y, m_color.z, 1
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
vec3 Cube::color() { return m_color; }

}
