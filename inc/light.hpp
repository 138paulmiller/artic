#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "color.hpp"

//base light representation
class Light{
public:
	Light(
	const Vec3f & pos,
	const Color & ambient,
	const Color & diffuse,
	const Color & specular);

	const Vec3f & pos() const;
	const Color & ambient()const;
	const Color & diffuse()const;
	const Color & specular()const;
private:
	Vec3f _pos;
	//intensities
	Color _ambient;
	Color _diffuse;
	Color _specular;
};

#endif	//LIGHT_HPP