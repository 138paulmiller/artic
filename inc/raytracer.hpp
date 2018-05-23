

#ifndef RAYTRACER_HPP
#define RAYTRACER_HPP
#include "shader.hpp"
#include "image.hpp"
#define DEFAULT_DEPTH 2
class RayTracer{
private:
	//nonowning pointers!
    Camera * _camera;
    Viewport * _viewport;
    Projection * _projection;
	Shader * _shader;
	Color _backgroundColor; //colored if not hit

public:
	RayTracer(Camera* camera, Viewport* viewport, Projection* projection, Shader* shader);
	void render(const Scene& scene, Image & image, int depth = DEFAULT_DEPTH);

	bool valid();

	void setBackgroundColor(const Color &  backgroundColor);
	void setCamera(Camera* camera);
	void setViewport(Viewport* viewport);
	void setProjection(Projection* projection);
	void setShader(Shader* shader);

protected:
	//checks intersection
	void castRay(const Ray3f & ray, const Scene & scene, Intersection& intersection);
	//determines color recursively
	Color trace(const Ray3f & ray, const Scene & scene, Intersection& intersection, int depth); 
};

#endif