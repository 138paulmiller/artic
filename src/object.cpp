#include "object.hpp"

Intersection::Intersection(){
	_object = nullptr;
	_distance = std::numeric_limits<double>::infinity();
}
//checks if new intersection 
inline void Intersection::update(Object * object, const Vec3f & poi, const Vec3f & normal, double distance){
	if(distance < _distance){
		_distance = distance;
		_object=object;
		_poi = poi;
		_normal = normal;
	}		
}
double Intersection::distance(){
	return _distance;
}
Vec3f Intersection::poi()const{
	return _poi;
}

Vec3f Intersection::normal()const{
	return _normal;
}

const Material* Intersection::material()const{
	return _object!=nullptr? _object->material() : nullptr; 
}	

const Object* Intersection::object()const{
	return _object; 
}

bool Intersection::valid()const{
	return _object != nullptr;
}

void Intersection::reset(){
	_object = nullptr;
	_distance = std::numeric_limits<double>::max();

}


/**************************************** Primitive Object Types ***************************************/
Sphere::Sphere(const Vec3f & center, double radius, Material * material)
	:Object(material){
	_center = center;
	_radius = radius;
	_radius2 = pow(radius, 2);
}

Sphere::~Sphere(){}

void Sphere::checkIntersection(const Ray3f & viewRay, Intersection & intersection){
	float t, t0, t1; 
	Vec3f look = _center - viewRay.origin();
	float tca = look.dot(viewRay.direction());
	// if (tca < 0) return false;
	float d = look.dot(look) - tca * tca;
	if (d > _radius2) 
		return;
	float thc = sqrt(_radius2 - d);
	t0 = tca - thc;
	t1 = tca + thc;
	t =  t0 < t1? t0 : t1;
	if (t < 0) {
		t = t1; // if t0 is negative, let's use t1 instead
		if (t < 0) 
			return; // both t0 and t1 are negative
	}
	//set poi and normal
	Vec3f poi = viewRay.point(t);
	Vec3f normal = (poi-_center).normal();
	intersection.update(this, poi, normal, t); 
}


