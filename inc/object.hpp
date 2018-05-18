#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "intersection.hpp"
#include "material.hpp"

/*************************************** Object *******************************************/
class Object{
public:
	Object(std::shared_ptr<Material> material=nullptr):_material(material) {}
	~Object();
	inline std::shared_ptr<Material> material() const {return _material;}
	virtual void checkIntersection(const Ray3f & viewRay, Intersection & intersection);
private:
	std::shared_ptr<Material> _material;
};


/*************************************** Object *******************************************/
class Sphere : public Object{
public:
	Sphere(std::shared_ptr<Material> material=nullptr);
	~Sphere();
	void checkIntersection(const Ray3f & viewRay, Intersection & intersection);
private:
	Vec3f _center;
	double radius;
};




#endif //OBJECT_HPP