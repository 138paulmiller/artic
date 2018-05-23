#include "object.hpp"

Intersection::Intersection(){
	_object = nullptr;
	_distance = std::numeric_limits<double>::infinity();
}
//checks if new intersection 
void Intersection::update(Object * object, const Vec3f & poi, const Vec3f & normal, double distance){
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

