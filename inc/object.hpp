#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <memory>
#include <limits>
#include "math.hpp"
#include "color.hpp"

using namespace math;
class Object;
class Material;
class Intersection;

/*************************************** Material *******************************************/
// For material blinn-phong coefficients see 
//	http://devernay.free.fr/cours/opengl/materials.html
struct Material{
	//Box for object material coefficients and colors
	// Color base;//surface color
	// Color emission;//color emitted
	//blinn-phong-phong coeff
	Color ambient;
	Color diffuse;
	Color specular;
	double shininess;
	double refraction;
	double reflection;

	Material(){}
	Material(	
	//	const Color &  base,		const Color & emission,
		const Color & ambient,	const Color & diffuse,	const Color & specular,	
		double shininess, double refraction, double reflection):
	ambient(ambient),	diffuse(diffuse), specular(specular),	
	shininess(shininess),refraction(refraction), reflection(reflection){}

};


/*************************************** Object *******************************************/
class Object{
private:
	Material* _material; //only reference, dow not delete
public:
	Object(Material * material=nullptr):_material(material) {}
	virtual ~Object(){}
	inline const Material * material() const 	{return _material;}
	//to be overriden
	virtual void checkIntersection(const Ray3f & viewRay, Intersection & intersection){}
};

/*************************************** Intersection *******************************************/
class Intersection{
	//encapsulates object intersection
private:
	double _distance; //distance, only updated when closer object intersects 
	Vec3f _poi; //opoint of intersection 
	Vec3f _normal; //opoint of intersection 
	Object * _object; //only reference, will not delete 
public:
	Intersection();
	//checks if new intersection 
	void update(Object * object, const Vec3f & poi, const Vec3f & normal, double distance);
	void setMaxDistance(double maxDistance);
	double distance();				
	Vec3f poi()const;
	Vec3f normal()const; 		
	const Material* material()const;	
	const Object* object()const;
	bool valid()const;
	void reset();
};


#endif //OBJECT_HPP