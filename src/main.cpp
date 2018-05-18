#include "raytracer.hpp"
#include "image.hpp"
void testPPM();

int main(){
	//testPPM();

	Image<HDR> img(480, 480);
	Scene scene;


	std::unique_ptr<Projection> projection;
	std::unique_ptr<Camera> camera;
	std::unique_ptr<Viewport> viewport;
	std::unique_ptr<Shader> shader;
	
	projection.reset(new PerspectiveProjection(1));
	camera.reset(new Camera({0,0,0}, {0,1,0}, {0,0,-1}));
	viewport.reset(new Viewport(img.width(), img.height(), -1,1,-1,1));
	shader.reset(new FlatShader());

	RayTracer rt(camera,viewport,projection, shader);

	rt.setBackgroundColor(HDR(1,0.4,0));

	rt.render(scene, img);

	Image<HDR>::exportPPM("OUT.ppm", img);

}



