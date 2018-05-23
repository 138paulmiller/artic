#include "light.hpp"

Light::Light(
	const Vec3f & pos,
	const Color & ambient,
	const Color & diffuse,
	const Color & specular)
	:_pos(pos), _ambient(ambient), 
	_diffuse(diffuse), _specular(specular)
	{}

const Vec3f & Light::pos() const{
	return _pos;
}
const Color & Light::ambient()const{
	return _ambient;
}
const Color & Light::diffuse()const{
	return _diffuse;
}
const Color & Light::specular()const{
	return _specular;
}