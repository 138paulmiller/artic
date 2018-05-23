

#ifndef RAYTRACER_HPP
#define RAYTRACER_HPP
#include "shader.hpp"
#include "image.hpp"

class RayTracer{
public:
	RayTracer(Camera* camera, Viewport* viewport, Projection* projection, Shader* shader);

	void render(const Scene& scene, Image & image );
	//returns true if hit
	Color trace(const Ray3f & viewRay, const Scene & scene, Intersection& intersection, int depth = 1); 

	void setBackgroundColor(const Color &  backgroundColor);

	void setCamera(Camera* camera);
	void setViewport(Viewport* viewport);
	void setProjection(Projection* projection);
	void setShader(Shader* shader);
	bool valid();

private:
	//nonowning pointers!
    Camera * _camera;
    Viewport * _viewport;
    Projection * _projection;
	Shader * _shader;
	Color _backgroundColor; //colored if not hit
};

#endif