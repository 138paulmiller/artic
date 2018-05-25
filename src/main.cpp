
#include "raytracer.hpp"
#include "primitives.hpp"
#include "image.hpp"

int main(){
	//testPPM();

	Image img(540, 480);

	//blinn-phong-phong coeff
	 Material gold(	
	 			Color(0.24725, 0.1995, 0.0745),//ambient 
				Color(0.75164, 0.60648, 0.22648), //diffuse
				Color(0.628281, 0.555802, 0.366065), //specular
				4, //shininess
				0.4, //refraction index
				0.1//reflectivity
				); 
	 Material ruby(
	 			Color(0.1745, 	0.01175, 	0.01175),//ambient 
				Color( 	0.61424, 	0.04136, 	0.04136), //diffuse
				Color(0.727811, 	0.626959, 	0.626959), //specular
				6,//shininess
				0.4, //refraction index
				0.1//reflectivity
				); 
	Material floor(	
				Color(0.0215, 	0.1745,	0.0215 	), 
				Color(0.07568, 	0.61424, 0.07568), 
				Color(0.633, 0.727811,	0.633), 
				100.0,
				0.0, //refraction index
				0.8//reflectivity
				);

	Material wall(
				Color(0.015, 	0.0335,	0.8215 	), 
				Color(0.068, 	0.424, 0.568), 
				Color(0.833, 0.927811,	0.933), 
				50.0,
				0.0,
				0.8
				);

	Scene scene;

	Vec3f center1 = Vec3f();
	Vec3f center2 = Vec3f({0,0,1});
	scene.addObject(std::make_shared<Sphere> (Vec3f({-3.5, 3.0, -7}), 2.0, &gold));
	scene.addObject(std::make_shared<Sphere> (Vec3f({3.5, -1.0, -8}), 3.0, &ruby));
	scene.addObject(std::make_shared<Plane> (Vec3f({0, 1, 0}), Vec3f({0,-2,-10}) , &floor));
	scene.addObject(std::make_shared<Plane> (Vec3f({0, 0, 1}), Vec3f({0,0,-10}) , &wall));

	int numShadowSamples = 200; 

	scene.addLight(std::make_shared<RectangleLight> (Vec3f({0, 6.0, -7.5}),  // pos
												Vec3f({0.0, 0.0, 1.0}),  //up
												Vec3f({0.0, 1.0, 0.0}),  //right
												Color(0.5, 1.00, 1.00),
												1.0, //intensity
												1.0, 1.0, //width, depth
												numShadowSamples));


	scene.addLight(std::make_shared<RectangleLight> (Vec3f({0.0, 5.5, -5.4}),  // pos
												Vec3f({0.0, 0.0, -1.0}),  //normal
												Vec3f({0.0, 1.0, 0.0}),  //right
												Color(1,0.99,0.99),
												1.0, //intensity
												2.0, 2.0, //width, depth
												numShadowSamples));

	scene.addLight(std::make_shared<RectangleLight> (Vec3f({0.0, 0.5, -5.4}),  // pos
												Vec3f({0.0, 0.0, -1.0}),  //normal
												Vec3f({0.0, 1.0, 0.0}),  //right
												Color(1,0.99,0.99),
												1.0, //intensity
												2.5, 2.5, //width, depth
												numShadowSamples));


	// scene.addLight(std::make_shared<RectangleLight> (Vec3f({-5.0, 0.5, -5.4}),  // pos
	// 											Vec3f({0.0, 0.0, -1.0}),  //normal
	// 											Vec3f({0.0, 1.0, 0.0}),  //right
	// 											Color(0,0,0.99),
	// 											1.0, //intensity
	// 											5.0, 5.0, //width, depth
	// 											numShadowSamples));


	Projection * projection =  new PerspectiveProjection(1);
//	Projection * projection =  new OrthographicProjection();
	Camera  *camera = new Camera({0,0,0}, {0,1,0}, {0,0,-1});
	Viewport * viewport =  new Viewport(img.width(), img.height(), -1,1,-1,1);
//	Shader * shader = new FlatShader();
	Shader * shader = new BlinnPhongShader();
	shader->setGlobalLight(Color(0.9,0.9,1));
	
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



