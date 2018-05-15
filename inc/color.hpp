#ifndef COLOR_HPP
#define COLOR_HPP

#define RGB_DEPTH 255
#define HDR_DEPTH 1

struct RGB;
struct HDR;

template <typename DEPTH>
struct Color{
	Color(DEPTH r=0, DEPTH g=0, DEPTH b=0);
	virtual ~Color(){}
	DEPTH r,g,b;
};
struct RGB : Color<char>{
	RGB(char r=0, char g=0, char b=0);
	RGB(const RGB & other);	
	const RGB & operator=(const RGB& other);
	HDR toHDR();
};

struct HDR : Color<double>{
	HDR(double  r=0, double g=0, double b=0);
	HDR(const HDR & other);
	const HDR & operator=(const HDR& other);
	RGB toRGB();
};

template <typename DEPTH>
Color<DEPTH>::Color(DEPTH r, DEPTH g, DEPTH b)
		:r(r), g(g), b(b){
}



#endif
