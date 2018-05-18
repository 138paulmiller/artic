#include "color.hpp"

RGB::RGB(char r, char g, char b)
	:_r(r),_g(g),_b(b){
	}

RGB::RGB(const RGB & other){
	*this = other;
}

const RGB & RGB::operator=(const RGB& other){
	set(other._r, other._g, other._b);
}

void RGB::set(char  r, char g, char b){
	_r = r;
	_g = g;
	_b = b;
}

char& RGB::r(){
	return _r;
}

char& RGB::g(){
	return _g;
}

char& RGB::b(){
	return _b;
}

HDR::HDR(double  r, double g, double b){
	HDR::set(r,g,b);
}

HDR::HDR(const HDR & other){
	*this = other;
}

const HDR & HDR::operator=(const HDR& other){
	HDR::set(other._r, other._g, other._b);

}

void HDR::set(double  r, double g, double b){
	RGB::set((int)(r*RGB_DEPTH), (int)(g*RGB_DEPTH), (int)(b*RGB_DEPTH));
}


