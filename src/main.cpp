
#include "raytracer.hpp"
#include "primitives.hpp"
#include "image.hpp"

int main(){
	//testPPM();

	Image img(640, 540);
//ADD SCENE LOADER to read the scene data from a file (possibly XML)
	//blinn-phong-phong coeff
	 Material gold(	
	 			Color(0.24725, 0.1995, 0.0745),//ambient 
				Color(0.75164, 0.60648, 0.22648), //diffuse
				Color(0.628281, 0.555802, 0.366065), //specular
				128*0.4, //shininess
				0.4, //refraction index
				0.1//reflectivity
				); 
	 Material ruby(
	 			Color(0.1745, 	0.01175, 	0.01175),//ambient 
				Color( 	0.61424, 	0.04136, 	0.04136), //diffuse
				Color(0.727811, 	0.626959, 	0.626959), //specular
				128*0.6,//shininess
				0.4, //refraction index
				0.1//reflectivity
				); 

	 Material test(
 			Color(0.02745, 	0.01175, 	0.071175),//ambient 
			Color(0.01424, 	0.4136, 	0.4136), //diffuse
			Color(1.0, 	1.0, 	1.0), //specular
			128*0.995,//shininess
			0.4, //refraction index
			0.1//reflectivity
			); 

	Material floor(	
				Color(0.523, 		0.1, 			0.06 ), 
				Color( 0.5012, 	0.50980392, 	0.50980392), 
				Color(0.50196078, 0.50196078, 0.50196078), 
				128*.25,
				0.0, //refraction index
				0.8//reflectivity
				);
	 	
	Material wall(
				Color(0.17811, 	0.026959, 	0.626959), 
				Color(0.43, 	0.5, 	0.0213), 
				Color(0.94, 0.17, 	0.7), 
				128*.10,
				0.0,
				0.8
				);

	Scene scene;

	Vec3f center1 = Vec3f();
	Vec3f center2 = Vec3f({0,0,1});
	scene.addObject(std::make_shared<Sphere> (Vec3f({-3.5, 3.0, -7}), 2.0, &gold));
	scene.addObject(std::make_shared<Sphere> (Vec3f({3.5, -1.0, -8}), 3.0, &ruby));
	scene.addObject(std::make_shared<Sphere> (Vec3f({0, 1.0, -2}), 1.0, &test));
	scene.addObject(std::make_shared<Plane> (Vec3f({0.0, 1, 0}), Vec3f({0,-2,-10}) , &floor));
	scene.addObject(std::make_shared<Plane> (Vec3f({0, 0, 1}), Vec3f({0,-2,-10}) , &wall));
	scene.addObject(std::make_shared<Plane> (Vec3f({-1, 0, 0}), Vec3f({5,-2,-10}) , &test));

	int numShadowSamples = 25; 

	scene.addLight(std::make_shared<RectangleLight> (
												Vec3f({5, 6.0, -7.5}),  // pos
												Vec3f({0.0, 0.0, 1.0}),  //up
												Vec3f({0.0, 1.0, 0.0}),  //right
												Color(1.0, 0.00, 0.00),
												1, //intensity
												1.0, 1.0, //width, depth
												numShadowSamples));


	scene.addLight(std::make_shared<RectangleLight> (Vec3f({0.0, 0, 0}),  // pos
												Vec3f({0.0, 0.0, -1.0}),  //normal
												Vec3f({0.0, 1.0, 0.0}),  //right
												Color(0.00,	1.00,	0.00),
												10, //intensity
												2.0, 2.0, //width, depth
												numShadowSamples));


	scene.addLight(std::make_shared<RectangleLight> (Vec3f({-3.0, 1.0, -3.4}),  // pos
												Vec3f({0.0, 0.0, -1.0}),  //normal
												Vec3f({0.0, 1.0, 0.0}),  //right
												Color(0.0, 0.0, 1.00),
												25, //intensity
												0.25, 0.25, //width, depth
												numShadowSamples));


	Projection * projection =  new PerspectiveProjection(1);
//	Projection * projection =  new OrthographicProjection();
	Camera  *camera = new Camera({0,2,0}, //pos
								{0,1,0}, //up 
								{0,-0.5,-1}); //view dir
	Viewport * viewport =  new Viewport(img.width(), img.height(), -1,1,-1,1);
//	Shader * shader = new FlatShader();
	Shader * shader = new BlinnPhongShader();
	shader->setGlobalLight(Color(1.0,1.0,1));
	
	RayTracer rt(camera,viewport,projection, shader);

	rt.setBackgroundColor(Color(0.0,0.0,0));
	if(rt.valid()){
		rt.render(scene, img);
		Image::exportPPM("OUT2.ppm", img);
		std::cout << "OUT";
	}
	delete shader;
	delete camera;
	delete projection;
	delete viewport;

}



