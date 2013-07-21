#ifndef __SHAPE_H__
#define __SHAPE_H__

///////////////////////////////////////////////// Shape

enum class shape_draw_t { LIST, INDEX };

class Shape {
public:
	Shape( shape_draw_t );
	virtual ~Shape();

	virtual void bind() = 0;
	virtual void render() = 0;

protected:
	GLfloat* m_vertices;
	GLfloat* m_colors;
	GLushort* m_indices;
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

	// update
	void bind();
	void render();

	// get
	float radius();
private:
	static const unsigned int CV = 32;	//count vertices
	static const unsigned int CI = 17;	//count indices
	float m_radius;
};


#endif //__SHAPE_H__
