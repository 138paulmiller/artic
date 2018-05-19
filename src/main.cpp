#include "raytracer.hpp"
#include "image.hpp"
void testPPM();

int main(){
	//testPPM();

	Image<HDR> img(480, 480);

	//blinn-phong-phong coeff
	Vec3f ambient = {0.24725, 0.1995, 0.0745};
	Vec3f diffuse=  {0.75164, 0.60648, 0.22648};
	Vec3f specular = { 0.628281, 0.555802, 0.366065};
	double shininess = {0.4};

	Material gold(ambient, diffuse, specular, shininess);
	Scene scene;

	Vec3f center = Vec3f({0,0,1});
	scene.addObject(std::make_shared<Sphere> (center, 0.15, &gold));

	std::unique_ptr<Projection> projection;
	std::unique_ptr<Camera> camera;
	std::unique_ptr<Viewport> viewport;
	std::unique_ptr<Shader> shader;
	
	projection.reset(new PerspectiveProjection(1));
	camera.reset(new Camera({0,0,0}, {0,1,0}, {0,0,1}));
	viewport.reset(new Viewport(img.width(), img.height(), -1,1,-1,1));
	shader.reset(new FlatShader());

	RayTracer rt(camera,viewport,projection, shader);

	rt.setBackgroundColor(Vec3f({1,0.0,0}));
	rt.render(scene, img);

	Image<HDR>::exportPPM("OUT.ppm", img);

}



