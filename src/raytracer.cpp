#include "raytracer.hpp"

RayTracer::RayTracer(
		Camera* camera,
		Viewport* viewport,
		Projection* projection,
		Shader* shader)
	:_camera(camera), 
	_viewport(viewport), 
	_projection(projection), 
	_shader(shader){
}

void RayTracer::setBackgroundColor(const Color & backgroundColor){
	_backgroundColor = backgroundColor;
}

void RayTracer::setCamera(Camera* camera){
	_camera = camera;
}

void RayTracer::setViewport(Viewport* viewport){
	_viewport = viewport;
}
void RayTracer::setProjection(Projection* projection){
	_projection = projection;
}

void RayTracer::setShader(Shader* shader){
	_shader = shader;
}


bool RayTracer::valid(){
	return _shader != nullptr 
		&& _projection != nullptr 
		&& _camera != nullptr 
		&& _viewport != nullptr;
}

void RayTracer::render(const Scene& scene, Image & image, int depth ){
	if(!valid()) return;
	Intersection intersection;
	Ray3f viewRay; 
	Color color;
	double u,v;
	for(int j = 0; j < image.height(); ++j ){	
		for(int i = 0; i < image.width(); ++i ){
			intersection.reset();
			_viewport->uv(u,v, i,j);
			_projection->getViewRay(viewRay, *_camera, u,v);
			color = trace(viewRay, scene, intersection, depth);
			image.pixel(i,j) = color;
		}
	}
}

void RayTracer::castRay(const Ray3f & ray, const Scene & scene, Intersection& intersection){
	for( auto const & object : scene.objects()){
		object->checkIntersection(ray, intersection);
	}
}

Color RayTracer::trace(const Ray3f & ray, const Scene & scene, Intersection& intersection, int depth){
	//traces the ray !
	//recursively follow the ray
	//if hit
	Color color(_backgroundColor);
	if(depth > 0 ){
		castRay(ray, scene, intersection);
		if(intersection.valid()){
			//trace the shadow, reflect and refract rays depending on material
			//shadow ray is from poi to light, if any lights produce shadow 
			_shader->shade(color, *_camera, scene, intersection);
			computeReflectColor(color, ray, scene, intersection, depth);
			//computeRefractColor(color, ray, scene, intersection, depth);
			computeShadowColor(color, ray, scene, intersection, depth);
		}
	}
	color.clamp(1);
	return color;
}

void RayTracer::computeReflectColor(Color & color, const Ray3f & ray, const Scene & scene, Intersection& intersection, int depth){
	Ray3f reflectRay;
	Intersection reflectIntersection;
	reflectRay.setOrigin(intersection.poi()+intersection.normal()*0.001);
	reflectRay.setDirection(ray.direction() - intersection.normal() * 2 * ray.direction().dot(intersection.normal()));
	reflectIntersection.setIgnoreObject(intersection.object());
	//compute reflect ray and retrace!, grab the color
	Color reflectColor = trace(reflectRay, scene, reflectIntersection, depth-1);
	double r = intersection.object()->material()->reflectivity;
	color = color +  reflectColor * r;

}

void RayTracer::computeRefractColor(Color & color, const Ray3f & ray, const Scene & scene, Intersection& intersection, int depth){

}

void RayTracer::computeShadowColor(Color & color, const Ray3f & ray, const Scene & scene, Intersection& intersection, int depth){
	// SEE : https://www.cs.unc.edu/~dm/UNC/COMP236/LECTURES/SoftShadows.pdf
	Ray3f shadowRay;
	Intersection shadowIntersection;
	Color totalColor(color);//default not change
	double numSamples = 0;
	double distance = 0;
	int  totalNumSamples = 0;
	for(auto const & light : scene.lights() ){
		//shadowColor=_backgroundColor;//default not change
		//set intersection distance to be between light and poi
		for(int i = 0; i < light->numSamples(); ++i){
			shadowIntersection.reset();
			shadowIntersection.setIgnoreObject(intersection.object());//prevent intersection of shadow ray with current intersecting object
			//if soft shadow, gather multiple samples and set color to the average of intersection ambient and background
			shadowRay = light->makeShadowRay(intersection.poi()+intersection.normal()*0.001, distance);
			shadowIntersection.setMaxDistance(distance);
			//only run once (depth = 1)
			castRay(shadowRay,scene, shadowIntersection);
			//if no intersection, increase color amount
			if(! shadowIntersection.valid()){
				//inverse square law 
				totalColor += (color*light->intensity()/pow(distance,2));
			}
		}
		totalNumSamples += light->numSamples();
	}
	//avg 
	color = (totalColor/totalNumSamples);// * totalIntensity/totalNumSamples ;
}

