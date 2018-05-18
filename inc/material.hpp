#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "color.hpp"
#include "math.hpp"
using namespace math;

/*************************************** Material *******************************************/
// For material blinn-phong coefficients see http://devernay.free.fr/cours/opengl/materials.html
struct Material{
	Material(){}
	Material(	
		const HDR &  base,
		const HDR & emission,
		const Vec3f & ambient,
		const Vec3f & diffuse,
		const Vec3f & specular,
		double shininess):
	base(base),
	emission(emission),
	ambient(ambient),
	diffuse(diffuse),
	specular(specular),
	shininess(shininess){}

	HDR base;//surface color
	HDR emission;//color emitted
	//blinn-phong-phong coeff
	Vec3f ambient;
	Vec3f diffuse;
	Vec3f specular;
	double shininess;
};


#endif //MATERIAL_HPP