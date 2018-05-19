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
	// HDR base;//surface color
	// HDR emission;//color emitted
	//blinn-phong-phong coeff
	Vec3f ambient;
	Vec3f diffuse;
	Vec3f specular;
	double shininess;

	Material(){}
	Material(	
	//	const HDR &  base,		const HDR & emission,
		const Vec3f & ambient,	const Vec3f & diffuse,
		const Vec3f & specular,	double shininess):
	//base(base),			emission(emission),
	ambient(ambient),	diffuse(diffuse),
	specular(specular),	shininess(shininess){}
	
};

/*************************************** Intersection *******************************************/
class Intersection{
	//encapsulates object intersection
private:
	double _distance; //distance, only update 
	Vec3f _poi; //opoint of intersection 
	Vec3f _normal; //opoint of intersection 
	Object * _object; //only reference, will not delete 
public:
	Intersection();
	//checks if new intersection 
	void update(Object * object, const Vec3f & poi, const Vec3f & normal,  double distance);
	double distance();				
	Vec3f poi()const;
	Vec3f normal()const; 		
	const Material* material()const;	
	const Object* object()const;
	bool valid()const;
	void reset();
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


/*************************************** Object *******************************************/
class Sphere : public Object{
private:
	Vec3f _center;
	double _radius;
	double _radius2; //squared 
public:
	Sphere(const Vec3f & center, double radius, Material* material);
	~Sphere();
	void checkIntersection(const Ray3f & viewRay, Intersection & intersection);

};




#endif //OBJECT_HPP