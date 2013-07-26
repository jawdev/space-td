#ifndef __LIGHT_H__
#define __LIGHT_H__
namespace jaw3d {

///////////////////////////////////////////////// Lighting
// Unified light model

enum class light_uloc_t { AMBIENT, COLOR, DIRECTION, LEN };

class Lighting {
public:
	Lighting();
	~Lighting();

	// update
	void locate_uniform( light_uloc_t, GLint );
	void bind();

	// set
	Lighting* ambient( vec3 );
	Lighting* color( vec3 );
	Lighting* direction( vec3 );

	// get
	vec3 ambient();
	vec3 color();
	vec3 direction();
private:
	vec3 m_ambient;	
	vec3 m_color;
	vec3 m_direction;
	GLint* m_uniforms;
};

} //jaw3d
#endif //__LIGHT_H__
