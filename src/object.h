#ifndef __OBJECT_H__
#define __OBJECT_H__
namespace jaw3d {

///////////////////////////////////////////////// Object

class Object {
public:
	Object();
	~Object();

	// load
	void load_shape( Shape* );

	// update
	void update( float dtime );
	void bind();
	void render();
	void bind_render() { bind(); render(); }

	// set
	void position( vec3 );
	void rotation( vec3 );
	void scale( vec3 );
	void velocity( vec3 );
	void spin( vec3 );
	void dscale( vec3 );

	// get
	vec3 position();
	vec3 rotation();
	vec3 scale();
	vec3 velocity();
	vec3 spin();
	vec3 dscale();
private:
	vec3 m_position;
	vec3 m_rotation;
	vec3 m_scale;
	vec3 m_velocity;
	vec3 m_spin;
	vec3 m_dscale;
	Shape* m_shape;
};

}
#endif //__OBJECT_H__
