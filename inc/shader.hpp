#ifndef SHADER_H
#define SHADER_H
#include "color.hpp"
#include "camera.hpp"
#include "scene.hpp"

class Shader{
protected:
	Color _globalLight;
public:
	Shader():_globalLight(1){}
	inline void setGlobalLight(Color globalLight){_globalLight = globalLight;}
	//assumes shade is called on a valid intersection
	virtual void shade( Color & color, const Camera& camera, const Scene& scene, const Intersection & intersection)=0;
};

class FlatShader : public Shader{
public:
	void shade(Color & color, const Camera& camera, const Scene& scene, const Intersection & intersection);
};

class BlinnPhongShader : public Shader{
public:
	void shade(Color & color, const Camera& camera, const Scene& scene, const Intersection & intersection);
};



#endif