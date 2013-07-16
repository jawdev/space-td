#include "config.h"

///////////////////////////////////////////////// Shape

Shape::Shape( shape_draw_t drawType ) {
	m_drawType = drawType;
	glGenVertexArrays( 1, m_va );
	if( drawType == LIST ) {
	} else if( drawType == INDEX ) {
		glGenBuffers( 1, m_vb );
		glGenBuffers( 1, m_eb );
	}
	construct();
}

Shape::~Shape() {

}

//----------------- update

void Shape::apply_matrix( vmath::mat4 matrix ) {
	for( unsigned int i = 0; i < m_countVertices; i++ ) {
		m_vertices[i] *= matrix;
	}
}


///////////////////////////////////////////////// Cube

Cube::Cube( float radius ) : Shape( INDEX ) {
	m_countVertices = 9;
}
