#include "light.hpp"

Light::Light(
	const Vec3f & position,
	const Color & color)
	:_pos(position), _color(color)
	{}

const Vec3f & Light::position() const{
	return _pos;
}
const Color & Light::color()const{
	return _color;
}
