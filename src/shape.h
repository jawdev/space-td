#ifndef __SHAPE_H__
#define __SHAPE_H__
namespace jaw3d {

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

///////////////////////////////////////////////// Line

class Line : public Shape {
public:
	Line( vec3 p1, vec3 p2, vec3 color=vec3( 1, 1, 1 ) );
	~Line();

	// update
	void bind();
	void render();

	// get
	vec3 p1();
	vec3 p2();
	vec3 color();
private:
	vec3 m_p1;
	vec3 m_p2;
	vec3 m_color;
};

///////////////////////////////////////////////// Cube

class Cube : public Shape {
public:
	Cube( float radius=1.0f, vec3 color=vec3( 1, 1, 1 ) );
	~Cube();

	// update
	void bind();
	void render();

	// get
	float radius();
	vec3 color();
private:
	static const unsigned int CV = 32;	//count vertices
	static const unsigned int CI = 17;	//count indices
	float m_radius;
	vec3 m_color;
};

}
#endif //__SHAPE_H__
