#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__
namespace jaw3d {

///////////////////////////////////////////////// vec2

struct vec2 {
	vec2( float _x=0.0f, float _y=0.0f, float _z=0.0f ) {
		x = _x;
		y = _y;
	}

	vec2& operator=( const vec2 &v ) {
		if( this == &v ) return *this;
		x = v.x;
		y = v.y;
		return *this;
	}
	vec2& operator+=( const vec2 &v ) {
		x += v.x;
		y += v.y;
		return *this;
	}
	
	vec2& operator-=( const vec2 &v ) {
		x -= v.x;
		y -= v.y;
		return *this;
	}
	vec2& operator*=( const float m ) {
		x *= m;
		y *= m;
		return *this;
	}
	vec2& operator/=( const float m ) {
		x /= m;
		y /= m;
		return *this;
	}
	const vec2 operator+( const vec2 &v ) const {
		vec2 result = *this;
		result += v;
		return result;
	}
	
	const vec2 operator-( const vec2 &v ) const {
		vec2 result = *this;
		result -= v;
		return result;
	}
	const vec2 operator*( const float m ) const {
		vec2 result = *this;
		result *= m;
		return result;
	}
	const vec2 operator/( const float m ) const {
		vec2 result = *this;
		result /= m;
		return result;
	}

	float x;
	float y;
};


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

///////////////////////////////////////////////// vec4

struct vec4 {
	vec4( float _x=0.0f, float _y=0.0f, float _z=0.0f, float _w=0.0f ) {
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	vec4& operator=( const vec4 &v ) {
		if( this == &v ) return *this;
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
		return *this;
	}
	vec4& operator+=( const vec4 &v ) {
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}
	
	vec4& operator-=( const vec4 &v ) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}
	vec4& operator*=( const float m ) {
		x *= m;
		y *= m;
		z *= m;
		w *= m;
		return *this;
	}
	vec4& operator/=( const float m ) {
		x /= m;
		y /= m;
		z /= m;
		w /= m;
		return *this;
	}
	const vec4 operator+( const vec4 &v ) const {
		vec4 result = *this;
		result += v;
		return result;
	}
	
	const vec4 operator-( const vec4 &v ) const {
		vec4 result = *this;
		result -= v;
		return result;
	}
	const vec4 operator*( const float m ) const {
		vec4 result = *this;
		result *= m;
		return result;
	}
	const vec4 operator/( const float m ) const {
		vec4 result = *this;
		result /= m;
		return result;
	}

	float x;
	float y;
	float z;
	float w;
};

///////////////////////////////////////////////// operators

}
#endif //__GEOMETRY_H__
