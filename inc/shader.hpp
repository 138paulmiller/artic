#ifndef SHADER_H
#define SHADER_H
#include "color.hpp"
#include "camera.hpp"
#include "scene.hpp"

class Shader{
public:
	virtual Vec3f shade(const Camera& camera, const Scene& scene, const Intersection & intersection)=0;

};

class FlatShader : public Shader{
public:
	Vec3f shade(const Camera& camera, const Scene& scene, const Intersection & intersection);
};

class BlinnPhongShader : public Shader{
public:
	Vec3f shade(const Camera& camera, const Scene& scene, const Intersection & intersection);
};



#endif