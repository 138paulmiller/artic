#include "image.hpp"

Image::Image(int width, int height){
	_pixels=0;
	resize(width,height);
}


Image::~Image(){
	delete []_pixels;
}


void Image::resize(int width, int height){
	if(width < 0 && height < 0)
		throw std::invalid_argument("Image width and height must be greater than 0");
	delete []_pixels;
	_width = width;
	_height = height;
	_pixels = new Color[_width*_height];
}


Color & Image::pixel(int x, int y){
	if(x <  0 || x >= _width || y < 0  || y >= _height )
		throw std::out_of_range("Out of Bounds_");
	return _pixels[y*_width+x];
}

const Color & Image::pixel(int x, int y) const{
	if(x <  0 || x >= _width || y < 0  || y >= _height )
		throw std::out_of_range("Out of Bounds_");
	return _pixels[y*_width+x];
}

int Image::width() const{
	return _width;
}

int Image::height() const{
	return _height;
}

void Image::exportPPM(std::string filename, const Image & img){
    std::ofstream ofs;
    ofs.open(filename, std::ios::out);
    ofs << "P6\n#"  << filename << "\n" 
                    << img.width() << "\n" << img.height() << "\n"
                    << RGB_DEPTH << "\n";
    int i =0;
    char bytes[3];
    for(int y=0; y<img.height(); y++) {
        for(int x=0; x<img.width(); x++) {
           	img.pixel(x,y).getBytes(bytes[0],bytes[1],bytes[2] );
            ofs.write((char*)bytes, 3);
        }
    }
    ofs.close();
}
