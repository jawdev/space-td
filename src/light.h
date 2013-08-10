#ifndef __LIGHT_H__
#define __LIGHT_H__
namespace jaw3d {

///////////////////////////////////////////////// Lighting
// Unified light model

enum class light_uloc_t { AMBIENT, COLOR, DIRECTION, _LEN };

class Light {
public:
	Light();
	virtual ~Light();

	// update
	void locate_uniform( light_uloc_t, GLint );
	virtual void bind();

protected:
	GLint* m_uniforms;
};


class DirectionLight : public Light {
public:
	DirectionLight( vec3 direction, vec3 color );
	~DirectionLight();

	// update
	void bind();

	// set
	DirectionLight* direction( vec3 );
	DirectionLight* color( vec3 );
	DirectionLight* ambient( vec3 );

	// get
	vec3 direction();
	vec3 color();
	vec3 ambient();
private:
	vec3 m_direction;
	vec3 m_color;
	vec3 m_ambient;
};

} //jaw3d
#endif //__LIGHT_H__
