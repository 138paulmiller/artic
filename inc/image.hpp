#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <typeinfo>
#include <stdexcept>
#include <string>
#include <fstream>
#include <iostream>
#include "color.hpp"

//RGB or HDR expected
class Image{
public:
	Image(int width, int height);
	~Image();
	void resize(int width, int height);
	Color & pixel(int x, int y);
	const Color & pixel(int x, int y) const;
	int width() const;
	int height() const;
	static void exportPPM(std::string filename, const Image& img);
private:
	Color * _pixels;
	int _width, _height;
};
#endif