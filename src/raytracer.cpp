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


void RayTracer::render(const Scene& scene, Image & image ){
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
			color = trace(viewRay, scene, intersection);
			image.pixel(i,j) = color;
		}
	}
}

Color RayTracer::trace(const Ray3f & viewRay, const Scene & scene, Intersection& intersection, int depth){
	//traces the ray !
	//recursively follow the ray
	//if hit
	Color color;
	for( auto const & object : scene.objects()){
		object->checkIntersection(viewRay, intersection);
	}
	if(intersection.valid())
		_shader->shade(color, *_camera, scene, intersection);
	else
		color =_backgroundColor;
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


