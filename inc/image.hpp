#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <typeinfo>
#include <stdexcept>
#include <string>
#include <fstream>
#include <iostream>
#include "color.hpp"

//RGB or HDR expected
template <typename COLOR>
class Image{
public:
	Image(int width, int height);
	~Image();

	void resize(int width, int height);

	COLOR & pixel(int x, int y);
	const COLOR & pixel(int x, int y) const;
	
	int width() const;
	int height() const;

	static void exportPPM(std::string filename, const Image<COLOR> & img);

private:
	COLOR * _pixels;
	int _width, _height;
};


template <typename COLOR>
Image<COLOR>::Image(int width, int height){
	if(typeid(COLOR) != typeid(HDR) && typeid(COLOR) != typeid(RGB))
		throw std::invalid_argument("Image expected HDR or RGB color types");
	_pixels =0;
	resize(width,height);
}

template <typename COLOR>
Image<COLOR>::~Image(){
	delete []_pixels;
}

template <typename COLOR>
void Image<COLOR>::resize(int width, int height){
	delete []_pixels;
	_width = width;
	_height = height;
	_pixels = new COLOR[_width*_height];
}

template <typename COLOR>
COLOR & Image<COLOR>::pixel(int x, int y){
	if(x <  0 || x >= _width || y < 0  || y >= _height )
		throw std::out_of_range("Out of Bounds_");
	return _pixels[y*_width+x];
}
template <typename COLOR>
const COLOR & Image<COLOR>::pixel(int x, int y) const{
	if(x <  0 || x >= _width || y < 0  || y >= _height )
		throw std::out_of_range("Out of Bounds_");
	return _pixels[y*_width+x];
}

template <typename COLOR>
int Image<COLOR>::width() const{
	return _width;
}


template <typename COLOR>
int Image<COLOR>::height() const{
	return _height;
}

template <typename COLOR>
void Image<COLOR>::exportPPM(std::string filename, const Image<COLOR> & img)
{
    std::ofstream ofs;
    ofs.open(filename, std::ios::out);
    ofs << "P6\n#"  << filename << "\n" 
                    << img.width() << "\n" << img.height() << "\n"
                    << RGB_DEPTH << "\n";
    int i =0;
    char bytes[3];
    RGB pixel;
    for(int y=0; y<img.height(); y++) {
        for(int x=0; x<img.width(); x++) {
            pixel = img.pixel(x,y);
            bytes[0]=pixel.r();
            bytes[1]=pixel.g();
            bytes[2]=pixel.b();
            ofs.write((char*)bytes, 3);
        }
    }
    ofs.close();
}


#endif