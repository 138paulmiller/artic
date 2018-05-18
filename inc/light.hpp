#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "math.hpp"
using namespace math;

//base light representation
class Light{
public:
	Light(Vec3f pos){}
private:
	Vec3f _pos;
};

#endif	//LIGHT_HPP