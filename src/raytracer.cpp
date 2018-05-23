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
			Ray3f shadowRay;
			Vec3f origin, dir;
			Intersection shadowIntersection;
			for(auto const& light : scene.lights() ){
				dir = (light->position() - intersection.poi());
				shadowIntersection.setMaxDistance(dir.magnitude());
				dir = dir.normal();
				origin = intersection.poi()+dir*0.1;
				//set the intersection distance to be between poi and light
				//poi may lay right on surface so will always intersect, move by epsilon toward light
				shadowRay.set(origin,  dir);
				//only run once (depth = 1)
				castRay(shadowRay, scene, shadowIntersection);
				if(shadowIntersection.valid())
					break;
			}
			//if not self intersection
			if(! shadowIntersection.valid() || shadowIntersection.object() == intersection.object())
				_shader->shade(color, *_camera, scene, intersection);
		}
	}

	return color;
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


