#ifndef COLOR_HPP
#define COLOR_HPP

#define RGB_DEPTH 255

#include <fstream>
#include <iostream>
#include "math.hpp"
using namespace math;

class Color : public Vec3f{
//Each color is a double between 0-1
public:
	Color(double  r=0, double g=0, double b=0):Vec3f({r,g,b}){}
	Color(const Color & other):Vec3f({other.r(),other.g(),other.b()}){}
	Color(const Vec3f & other):Vec3f(other){}
	inline double& r(){return (*this)[0];}
	inline double& g(){return (*this)[1];}
	inline double& b(){return (*this)[2];}
	inline const double& r()const {return (*this)[0];}
	inline const double& g()const {return (*this)[1];}
	inline const double& b()const {return (*this)[2];}
	inline void set(double r, double g, double b){
		(*this)[0] = r;(*this)[1] = g; (*this)[2] = b;
	}
	//used to generate 0-RGB_DEPTH color components for PPM export
	inline void getBytes(char & r, char & g, char  b)const{
			r = (char)((*this)[0]*RGB_DEPTH);
			g = (char)((*this)[1]*RGB_DEPTH);
			b = (char)((*this)[2]*RGB_DEPTH);
	}
};

#endif
