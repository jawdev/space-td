#ifndef __SHAPE_H__
#define __SHAPE_H__
namespace jaw3d {

///////////////////////////////////////////////// Shape

class Shape {
public:
	Shape( vec4 color );
	virtual ~Shape();

	virtual void bind() = 0;
	virtual void render() = 0;

	// get
	vec4 color();
protected:
	vec4 shape_color;
};

///////////////////////////////////////////////// Plane

class FloorPlane : public Shape {
public:
	FloorPlane( float width, float length, vec4 color=vec4() );
	~FloorPlane();

	// update
	void bind();
	void render();

	// get
	float width();
	float length();
private:
	static const unsigned int CV = 3*4*2;
	static const unsigned int CN = 3*3*2;
	float m_width;
	float m_length;
	GLuint m_va;
	GLuint m_vb;
	GLfloat* m_vertices;
	GLfloat* m_normals;
};

///////////////////////////////////////////////// Cube

class Cube : public Shape {
public:
	Cube( float radius=1.0f, vec4 color=vec4() );
	~Cube();

	// update
	void bind();
	void render();

	// get
	float radius();
private:
	static const unsigned int CV = 2*3*4*6;	//count vertices
	static const unsigned int CN = 2*3*3*6; //count normals
	float m_radius;
	GLuint m_va;
	GLuint m_vb;
	GLfloat* m_vertices;
	GLfloat* m_normals;
};

} //jaw3d
#endif //__SHAPE_H__
