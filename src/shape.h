#ifndef __SHAPE_H__
#define __SHAPE_H__

///////////////////////////////////////////////// Shape

enum shape_draw_t class { LIST, INDEX };

class Shape {
public:
	Shape( shape_draw_t );
	~Shape();

	// update
	void apply_matrix( vmath::vec4 );

protected:
	unsigned int m_countVertices;
	unsigned int m_countColors;
	unsigned int m_countIndices;
	vmath::vec4 m_vertices[];
	vmath::vec4 m_colors[];
	GLuint m_indices[];

	virtual void construct() = 0;
private:
	GLuint m_va;
	GLuint m_vb;
	GLuint m_eb;
	shape_draw_t m_drawType;
};

///////////////////////////////////////////////// Cube

class Cube : public Shape {
public:
	Cube( float radius=1.0f );
	~Cube();

	// get
	float radius();
private:
	float m_radius;
};

#endif //__SHAPE_H__
