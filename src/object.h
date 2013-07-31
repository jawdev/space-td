#ifndef __OBJECT_H__
#define __OBJECT_H__
namespace jaw3d {

///////////////////////////////////////////////// Object

enum class obj_uloc_t { MODEL, NORMAL, LEN };

class Object {
public:
	Object();
	~Object();

	// load
	void load_shape( Shape* );
	void locate_uniform( obj_uloc_t, GLint loc );

	// update
	void update( float dtime );
	void bind();
	void render();
	void bind_render();

	// set
	Object* allow_update( bool=true );
	Object* allow_render( bool=true );
	Object* position( vec3 );
	Object* rotation( vec3 );
	Object* scale( vec3 );
	Object* velocity( vec3 );
	Object* spin( vec3 );
	Object* dscale( vec3 );

	// get
	bool allow_update();
	bool allow_render();
	vec3 position();
	vec3 rotation();
	vec3 scale();
	vec3 velocity();
	vec3 spin();
	vec3 dscale();
private:
	bool m_update;
	bool m_render;
	vec3 m_position;
	vec3 m_rotation;
	vec3 m_scale;
	vec3 m_velocity;
	vec3 m_spin;
	vec3 m_dscale;
	Shape* m_shape;
	GLint* m_uniforms;
};

}
#endif //__OBJECT_H__
