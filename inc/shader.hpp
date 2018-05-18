#ifndef SHADER_H
#define SHADER_H
#include "color.hpp"
#include "camera.hpp"
#include "scene.hpp"

class Shader{
public:
	virtual HDR shade(const Camera& camera, const Scene& scene, const Intersection & intersection)=0;

};

class FlatShader : public Shader{
public:
	HDR shade(const Camera& camera, const Scene& scene, const Intersection & intersection);
};

class BlinnPhongShader : public Shader{
public:
	HDR shade(const Camera& camera, const Scene& scene, const Intersection & intersection);
};



#endif