#ifndef __SHAPE_H__
#define __SHAPE_H__
namespace jaw3d {

///////////////////////////////////////////////// Shape

class Shape {
public:
	Shape();
	virtual ~Shape();

	virtual void bind() = 0;
	virtual void render() = 0;

protected:
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
	vec4 color();
private:
	static const unsigned int CV = 2*3*4*6;	//count vertices
	static const unsigned int CN = 2*3*3*6; //count normals
	float m_radius;
	vec4 m_color;
	GLuint m_va;
	GLuint m_vb;
	GLfloat* m_vertices;
	GLfloat* m_normals;
};

} //jaw3d
#endif //__SHAPE_H__
