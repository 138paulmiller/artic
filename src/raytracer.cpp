#include "raytracer.hpp"

RayTracer::RayTracer(
		std::unique_ptr<Camera>& camera,
		std::unique_ptr<Viewport>& viewport,
		std::unique_ptr<Projection>& projection,
		std::unique_ptr<Shader> & shader)
	:_camera(std::move(camera)), 
	_viewport(std::move(viewport)), 
	_projection(std::move(projection)), 
	_shader(std::move(shader)){
}


void RayTracer::render(const Scene& scene, Image<HDR> & image ){
	if(!ready()) return;
	Intersection intersection;
	Ray3f viewRay; 
	Vec3f color;
	double u,v;
	for(int j = 0; j < image.height(); ++j ){	
		for(int i = 0; i < image.width(); ++i ){
			intersection.reset();
			_viewport->uv(u,v, i,j);
			_projection->getViewRay(viewRay, *_camera, u,v);
			color = trace(viewRay, scene, intersection);
			image.pixel(i,j).set(color[0], color[1], color[2]);
		}
	}
}

Vec3f RayTracer::trace(const Ray3f & viewRay, const Scene & scene, Intersection& intersection, int depth){
	//traces the ray !
	//recursively follow the ray
	//if hit
	for( auto const & object : scene.objects()){
		object->checkIntersection(viewRay, intersection);
	}
	if(intersection.valid())

		return _shader->shade(*_camera, scene, intersection);
	return _backgroundColor;
}

void RayTracer::setBackgroundColor(Vec3f backgroundColor){
	_backgroundColor = backgroundColor;
}


void RayTracer::resetCamera(std::unique_ptr<Camera>& camera){
	_camera.reset();
	_camera = std::move(camera);
}

void RayTracer::resetViewport(std::unique_ptr<Viewport>& viewport){
	_viewport.reset();
	_viewport = std::move(viewport);
}
void RayTracer::resetProjection(std::unique_ptr<Projection>& projection){
	_projection.reset();
	_projection = std::move(projection);
}

void RayTracer::resetShader(std::unique_ptr<Shader>& shader){
	_shader.reset();
	_shader = std::move(shader);
}


bool RayTracer::ready(){
	return _shader != nullptr 
		&& _projection != nullptr 
		&& _camera != nullptr 
		&& _viewport != nullptr;
}


