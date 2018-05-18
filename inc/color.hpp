#ifndef COLOR_HPP
#define COLOR_HPP

#define RGB_DEPTH 255

class RGB {
public:
	RGB(char r=0, char g=0, char b=0);
	RGB(const RGB & other);
	const RGB & operator=(const RGB& other);
	virtual void set(char r, char g, char b);
	char& r();
	char& g();
	char& b();
protected:
	char _r,_g,_b;

};

class HDR : public RGB{
public:
	HDR(double  r=0, double g=0, double b=0);
	HDR(const HDR & other);
	const HDR & operator=(const HDR& other);
	void set(double r, double g, double b);
};

#endif
