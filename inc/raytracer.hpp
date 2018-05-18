

#ifndef RAYTRACER_HPP
#define RAYTRACER_HPP
#include "shader.hpp"
#include "image.hpp"

class RayTracer{
public:
	RayTracer(
		std::unique_ptr<Camera>& camera,
		std::unique_ptr<Viewport>& viewport,
		std::unique_ptr<Projection>& projection,
		std::unique_ptr<Shader> & shader);

	void render(const Scene& scene, Image<HDR> & image );
	//returns true if hit
	HDR trace(const Ray3f & viewRay, const Scene & scene, Intersection& intersection, int depth = 1); 

	void setBackgroundColor(HDR backgroundColor);

	void resetCamera(const HDR & backgroundColor);
	void resetCamera(std::unique_ptr<Camera>& camera);
	void resetViewport(std::unique_ptr<Viewport>& viewport);
	void resetProjection(std::unique_ptr<Projection>& projection);
	void resetShader(std::unique_ptr<Shader>& shader);

	bool ready();

private:
    std::unique_ptr<Camera> _camera;
    std::unique_ptr<Viewport> _viewport;
    std::unique_ptr<Projection> _projection;
	std::unique_ptr<Shader> _shader;
	HDR _backgroundColor; //colored if not hit
};

#endif