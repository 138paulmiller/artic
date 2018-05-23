
#include "raytracer.hpp"
#include "primitives.hpp"
#include "image.hpp"

int main(){
	//testPPM();

	Image img(480, 480);

	//blinn-phong-phong coeff
	 Material gold(	Color(0.24725, 0.1995, 0.0745),//ambient 
					Color(0.75164, 0.60648, 0.22648), //diffuse
					Color(0.628281, 0.555802, 0.366065), //specular
					0.4);//shininess
	Material mat2(	Color(0.2,0.7,0.0), 
					Color(0.2,0.4,0), 
					Color(0.0, 0.01,0.6), 
					0.6);

	Scene scene;

	Vec3f center1 = Vec3f();
	Vec3f center2 = Vec3f({0,0,1});
	scene.addObject(std::make_shared<Sphere> (Vec3f({0.5, -1.0,2}), 0.5, &gold));
	scene.addObject(std::make_shared<Sphere> (Vec3f({-0.5, 1.0, 2}), 0.5, &gold));
	scene.addObject(std::make_shared<Plane> (Vec3f({0,  1, 0}), Vec3f({0,-1,1}) , &mat2));

	scene.addLight(std::make_shared<Light> (Vec3f({-1,  1, 0}), Color(0.3,1,1),	Color(1,1,1),	Color(0.5,0.6,0.3)));
	//scene.addLight(std::make_shared<Light> (Vec3f({1,  1, 1}), 	Color(1,1,1),	Color(1,1,1),	Color(0.4,1,1)));


	Projection * projection =  new PerspectiveProjection(1);
//	Projection * projection =  new OrthographicProjection();
	Camera  *camera = new Camera({0,0,0}, {0,1,0}, {0,0,1});
	Viewport * viewport =  new Viewport(img.width(), img.height(), -1,1,-1,1);
//	Shader * shader = new FlatShader();
	Shader * shader = new BlinnPhongShader();
	
	RayTracer rt(camera,viewport,projection, shader);

	rt.setBackgroundColor(Color(0.0,0.0,0));
	if(rt.valid()){
		rt.render(scene, img);
		Image::exportPPM("OUT.ppm", img);
		std::cout << "OUT";
	}
	delete shader;
	delete camera;
	delete projection;
	delete viewport;

}



