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
}

FloorPlane::~FloorPlane() {
	delete [] m_vertices;
	delete [] m_normals;
}

//----------------- update

void FloorPlane::bind() {
	glEnable( GL_CULL_FACE );
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
}

Cube::~Cube() {
	delete [] m_vertices;
	delete [] m_normals;
}

//----------------- update

void Cube::bind() {
	glEnable( GL_CULL_FACE );
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

///////////////////////////////////////////////// Sphere

Sphere::Sphere( float r, unsigned int q, vec4 color ) : Shape( color ) {
	m_radius = r;
	m_quality = q;
	glGenVertexArrays( 1, &m_va );
	glGenBuffers( 1, &m_vb );

	m_faces = 2*( 2*q*q+8*q+6 + 2*q+6 ); //+22;
	m_vc = m_faces*3*4;
	m_nc = m_faces*3*3;

	m_vertices = new GLfloat[m_vc];
	m_normals = new GLfloat[m_nc];

	unsigned int vi = 0;
	unsigned int ni = 0;
	float dx = 2*PI/float( 2*q+6 );
	float dy = PI/float( q+3 );
	float pi_2 = PI/2.0f;
	for( unsigned int i = 1; i < q+2; i++ ) {
		float theta1 = pi_2-i*dy;
		float theta2 = pi_2-( i+1 )*dy;
		float rad1 = r*cos( theta1 );
		float rad2 = r*cos( theta2 );
		float y1 = r*sin( theta1 );
		float y2 = r*sin( theta2 );
		for( unsigned int j = 0; j < 2*q+6; j++ ) {
			float phi1 = j*dx;
			float phi2 = ( j+1 )*dx;
			float x1 = rad1*cos( phi1 );
			float x2 = rad1*cos( phi2 );
			float x3 = rad2*cos( phi1 );
			float x4 = rad2*cos( phi2 );
			float z1 = rad1*sin( phi1 );
			float z2 = rad1*sin( phi2 );
			float z3 = rad2*sin( phi1 );
			float z4 = rad2*sin( phi2 );
			m_vertices[vi++] = x1; m_vertices[vi++] = y1; m_vertices[vi++] = z1; m_vertices[vi++] = 1.0f;
			m_vertices[vi++] = x2; m_vertices[vi++] = y1; m_vertices[vi++] = z2; m_vertices[vi++] = 1.0f;
			m_vertices[vi++] = x4; m_vertices[vi++] = y2; m_vertices[vi++] = z4; m_vertices[vi++] = 1.0f;
			m_vertices[vi++] = x1; m_vertices[vi++] = y1; m_vertices[vi++] = z1; m_vertices[vi++] = 1.0f;
			m_vertices[vi++] = x4; m_vertices[vi++] = y2; m_vertices[vi++] = z4; m_vertices[vi++] = 1.0f;
			m_vertices[vi++] = x3; m_vertices[vi++] = y2; m_vertices[vi++] = z3; m_vertices[vi++] = 1.0f;
			m_normals[ni++] = cos( phi1 ); m_normals[ni++] = sin( theta1 ); m_normals[ni++] = sin( phi1 );
			m_normals[ni++] = cos( phi2 ); m_normals[ni++] = sin( theta1 ); m_normals[ni++] = sin( phi2 );
			m_normals[ni++] = cos( phi2 ); m_normals[ni++] = sin( theta2 ); m_normals[ni++] = sin( phi2 );
			m_normals[ni++] = cos( phi1 ); m_normals[ni++] = sin( theta1 ); m_normals[ni++] = sin( phi1 );
			m_normals[ni++] = cos( phi2 ); m_normals[ni++] = sin( theta2 ); m_normals[ni++] = sin( phi2 );
			m_normals[ni++] = cos( phi1 ); m_normals[ni++] = sin( theta2 ); m_normals[ni++] = sin( phi1 );
		}
	}
	float ca = pi_2-dy;
	float c = r*cos( ca );
	for( unsigned int i = 0; i < 2*q+6; i++ ) {
		float t1 = i*dx;
		float t2 = ( i+1 )*dx;
		m_vertices[vi++] = 0; m_vertices[vi++] = r; m_vertices[vi++] = 0; m_vertices[vi++] = 1.0f;
		m_vertices[vi++] = c*cos( t2 ); m_vertices[vi++] = r*sin( ca ); m_vertices[vi++] = c*sin( t2 ); m_vertices[vi++] = 1.0f;
		m_vertices[vi++] = c*cos( t1 ); m_vertices[vi++] = r*sin( ca ); m_vertices[vi++] = c*sin( t1 ); m_vertices[vi++] = 1.0f;
		m_vertices[vi++] = 0; m_vertices[vi++] = -r; m_vertices[vi++] = 0; m_vertices[vi++] = 1.0f;
		m_vertices[vi++] = c*cos( t1 ); m_vertices[vi++] = -r*sin( ca ); m_vertices[vi++] = c*sin( t1 ); m_vertices[vi++] = 1.0f;
		m_vertices[vi++] = c*cos( t2 ); m_vertices[vi++] = -r*sin( ca ); m_vertices[vi++] = c*sin( t2 ); m_vertices[vi++] = 1.0f;
		m_normals[ni++] = 0; m_normals[ni++] = 1; m_normals[ni++] = 0;
		m_normals[ni++] = cos( t2 ); m_normals[ni++] = sin( ca ); m_normals[ni++] = sin( t2 );
		m_normals[ni++] = cos( t1 ); m_normals[ni++] = sin( ca ); m_normals[ni++] = sin( t1 );
		m_normals[ni++] = 0; m_normals[ni++] = -1; m_normals[ni++] = 0;
		m_normals[ni++] = cos( t1 ); m_normals[ni++] = -sin( ca ); m_normals[ni++] = sin( t1 );
		m_normals[ni++] = cos( t2 ); m_normals[ni++] = -sin( ca ); m_normals[ni++] = sin( t2 );
	}

	glBindVertexArray( m_va );
	glBindBuffer( GL_ARRAY_BUFFER, m_vb );
	glBufferData( GL_ARRAY_BUFFER, ( m_vc+m_nc )*sizeof( GLfloat ), NULL, GL_STATIC_DRAW );
	glBufferSubData( GL_ARRAY_BUFFER, 0, m_vc*sizeof( GLfloat ), m_vertices );
	glBufferSubData( GL_ARRAY_BUFFER, m_vc*sizeof( GLfloat ), m_nc*sizeof( GLfloat ), m_normals );

	glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 0, 0 );
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (const void*)( m_vc*sizeof( GLfloat ) ) );
	glEnableVertexAttribArray( 0 );
	glEnableVertexAttribArray( 1 );
}

Sphere::~Sphere() {
	delete [] m_vertices;
	delete [] m_normals;
}

//----------------- update

void Sphere::bind() {
	vmath::vec4 v( shape_color.x, shape_color.y, shape_color.z, shape_color.w );
	glVertexAttrib4fv( 2, v );
	glBindVertexArray( m_va );
	glBindBuffer( GL_ARRAY_BUFFER, m_vb );
}

void Sphere::render() {
	glDrawArrays( GL_TRIANGLES, 0, m_faces*3.0f );
}
} //jaw3d
