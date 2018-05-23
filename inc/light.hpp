#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "color.hpp"

//base light representation
class Light{
public:
	Light(
	const Vec3f & position,
	const Color & color);

	const Vec3f & position() const;
	const Color & color()const;
private:
	Vec3f _pos;
	//intensities
	Color _color;
};

#endif	//LIGHT_HPP