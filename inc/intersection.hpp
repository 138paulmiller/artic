#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include <limits>
#include <memory>
#include "color.hpp"
#include "math.hpp"

using namespace math;

class Object; //forward decl
/*************************************** Intersection *******************************************/
class Intersection{
public:
	Intersection(){
		_object = nullptr;
		_distance = std::numeric_limits<double>::infinity();

	}
	//checks if new intersection 
	inline void update(Vec3f poi, Vec3f normal, Object * object, double distance){
		if(distance < _distance){
			_poi=poi;
			_normal=normal;
			_distance = distance;
			_object=object;
		}		
	}
	inline double distance()			{return _distance;}
	inline Vec3f poi()const 			{return _poi;}
	inline Vec3f normal()const 			{return _normal;}
	inline const Object* object()const	{return _object; }
		
	inline bool valid()const 			{return _object != nullptr;}
	inline void reset() 				{_object = nullptr;}
private:
	double _distance; //distance, only update 
	Vec3f _poi; //point of intersection
	Vec3f _normal; //surface normal
	Object * _object; //only reference, will not delete
	
};



#endif //INTERSECTION