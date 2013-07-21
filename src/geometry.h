#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__
namespace jaw3d {

///////////////////////////////////////////////// vec3

struct vec3 {
	vec3( float _x=0.0f, float _y=0.0f, float _z=0.0f ) {
		x = _x;
		y = _y;
		z = _z;
	}

	vec3& operator=( const vec3 &v ) {
		if( this == &v ) return *this;
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}
	vec3& operator+=( const vec3 &v ) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	
	vec3& operator-=( const vec3 &v ) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	vec3& operator*=( const float m ) {
		x *= m;
		y *= m;
		z *= m;
		return *this;
	}
	vec3& operator/=( const float m ) {
		x /= m;
		y /= m;
		z /= m;
		return *this;
	}
	const vec3 operator+( const vec3 &v ) const {
		vec3 result = *this;
		result += v;
		return result;
	}
	
	const vec3 operator-( const vec3 &v ) const {
		vec3 result = *this;
		result -= v;
		return result;
	}
	const vec3 operator*( const float m ) const {
		vec3 result = *this;
		result *= m;
		return result;
	}
	const vec3 operator/( const float m ) const {
		vec3 result = *this;
		result /= m;
		return result;
	}

	float x;
	float y;
	float z;
};

}
#endif //__GEOMETRY_H__
