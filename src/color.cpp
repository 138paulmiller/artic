#include <iostream>
#include "color.hpp"
RGB::RGB(char r, char g, char b)
	:Color<char>(r,g,b){
}
RGB::RGB(const RGB & other)
	:Color<char>(other.r,other.g,other.b){
}
const RGB & RGB::operator=(const RGB & other){
	r= other.r,
	g= other.g,
	b = other.b;
}


HDR RGB::toHDR(){return HDR((double)(r)/RGB_DEPTH,(double)(g)/RGB_DEPTH,(double)(b)/RGB_DEPTH);}

HDR::HDR(double  r, double g, double b)
	:Color<double>(r,g,b){
}
HDR::HDR(const HDR & other)
	:Color<double>(other.r,other.g,other.b){
}

const HDR & HDR::operator=(const HDR & other){
	r= other.r,
	g= other.g,
	b = other.b;
}


RGB HDR::toRGB(){
	char _r = (int)(r*RGB_DEPTH),
		 _g = (int)(g*RGB_DEPTH),
		 _b = (int)(b*RGB_DEPTH);
	return RGB(_r, _g, _b);
}
