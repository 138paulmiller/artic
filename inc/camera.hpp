#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "math.hpp"
#include <memory>
/*
	Contains camera and, projection, and viewport classes
	
*/
using namespace math;
class Camera;
class Viewport;
class Orthographic;
class Perspective;
//abstract
class Projection;


/****************************** Camera ***********************/
class Camera{
public:
	Camera(Vec3f eye, Vec3f up, Vec3f dir);
	const Vec3f & eye()const;
	const Vec3f & u()const;
	const Vec3f & v()const;
	const Vec3f & w()const;
private:
 	math::Vec3f _eye, _u, _v, _w;
};


/****************************** Viewport ***********************/
class Viewport{
public:
	Viewport(int xResolution, int yResolution, 
			double left, double right, double top, double bottom);
	//compute image i,j in 2D to viewplane u,v in 3D space
	void uv(double& u, double& v, int i,int j);
private:
	double _left, _right, _top, _bottom; 
	int _xResolution, _yResolution; 
};

/****************************** Projections ***********************/
//abstract
class Projection{
public:
	virtual void getViewRay(math::Ray3f & viewRay, const Camera & cam, double u, double v) const = 0;
};

class OrthographicProjection: public Projection{
public:
	void getViewRay(math::Ray3f & viewRay, const Camera & cam, double u, double v) const;
};

class PerspectiveProjection: public Projection{
public:
	PerspectiveProjection(double focalLength);
	void getViewRay(math::Ray3f & viewRay, const Camera & cam, double u, double v) const;
private:
	double _focalLength;
};


#endif