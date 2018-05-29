
#include "raytracer.hpp"
#include "primitives.hpp"
#include "image.hpp"
#include "args.hpp"

int main(int argc, char ** argv){
	//testPPM();
	Args args(argc, argv);
	std::string outfile = args.getString( "-out", "images/out.ppm");
	//recursion depth
	int depth = args.getInt("-depth", 25);

	int numSamples = args.getInt("-depth", 10);
	
	std::vector<float> params;
	args.getFloats(params, "-material", ',');
	
	Image img(640, 540);
	//ADD SCENE LOADER to read the scene data from a file (possibly XML)
	//blinn-phong-phong coeff
	
	Material gold(	
		Color(0.24725, 0.1995, 0.0745),//ambient 
		Color(0.75164, 0.60648, 0.22648), //diffuse
		Color(0.628281, 0.555802, 0.366065), //specular
		128*0.4, //shininess	
		0.23, //transparency
		0.4, //refraction index
		0.1//reflectivity
		); 

	Material ruby(
		Color(0.1745, 	0.01175, 	0.01175),//ambient 
		Color( 	0.61424, 	0.04136, 	0.04136), //diffuse
		Color(0.727811, 	0.626959, 	0.626959), //specular
		128*0.6,//shininess
		0.99, //transparency
		0.4, //refraction index
		0.1//reflectivity
		); 

	Material test(
		Color(0.02745, 	0.01175, 	0.071175),//ambient 
		Color(0.01424, 	0.4136, 	0.4136), //diffuse
		Color(1.0, 	1.0, 	1.0), //specular
		128*0.995,//shininess
		0.12, //transparency
		0.4, //refraction index
		0.01//reflectivity
		); 

	Material floor(	
		Color(0.0523, 		0.1, 			0.6 ), 
		Color( 0.0012, 	0.00980392, 	0.1980392), 
		Color(0.80196078, 0.771078, 0.70196078), 
		128*.25, //shininess
		0.5, //transparency
		0.0, //refraction index
		0.8//reflectivity
		);
	 	
	Material wall(
		Color(0.17811, 	0.026959, 	0.626959), 
		Color(0.43, 	0.5, 	0.0213), 
		Color(0.94, 0.17, 	0.7), 
		128*.10, //shininess
		0.0, //transparency
		0.0, //refraction index
		0.08	//reflectivity
		);

	Scene scene;

 

	scene.addLight(std::make_shared<RectangleLight> (
		Vec3f({5, 6.0, -7.5}),  // pos
		Vec3f({0.0, 0.0, 1.0}),  //up
		Vec3f({0.0, 1.0, 0.0}),  //right
		Color(1.0, 0.00, 0.00),
		1, //intensity
		1.0, 1.0, //width, depth
		numSamples));


	// scene.addLight(std::make_shared<RectangleLight> (
	// 	Vec3f({0.0, 0, 0}),  // pos
	// 	Vec3f({0.0, 0.0, -1.0}),  //normal
	// 	Vec3f({0.0, 1.0, 0.0}),  //right
	// 	Color(0.00,	1.00,	0.00),
	// 	10, //intensity
	// 	2.0, 2.0, //width, depth
	// 	numSamples));


	scene.addLight(std::make_shared<RectangleLight> (
		Vec3f({-3.0, 1.0, -3.4}),  // pos
		Vec3f({0.0, 0.0, -1.0}),  //normal
		Vec3f({0.0, 1.0, 0.0}),  //right
		Color(0.0, 0.0, 1.00),
		25, //intensity
		0.25, 0.25, //width, depth
		numSamples));


	scene.addObject(std::make_shared<Sphere> (Vec3f({-3.5, 3.0, -7}), 2.0, &ruby));
	scene.addObject(std::make_shared<Sphere> (Vec3f({3.5, -1.0, -8}), 3.0, &gold));
	scene.addObject(std::make_shared<Sphere> (Vec3f({0, 1.0, -2}), 1.0, &test));
	scene.addObject(std::make_shared<Plane> (Vec3f({0.0, 1, 0}), Vec3f({0,-2,-10}) , &floor));
	scene.addObject(std::make_shared<Plane> (Vec3f({0, 0, 1}), Vec3f({0,-2,-10}) , &wall));
	scene.addObject(std::make_shared<Plane> (Vec3f({-1, 0, 0}), Vec3f({5,-2,-10}) , &test));
	scene.addObject(std::make_shared<Plane> (Vec3f({0, 0, -1}), Vec3f({0,0,2}) , &test));
	Projection * projection =  new PerspectiveProjection(1);
	//Projection * projection =  new OrthographicProjection();
	Camera  *camera = new Camera({0,2,0}, //pos
								{0,1,0}, //up 
								{0,-0.5,-1}); //view dir
	Viewport * viewport =  new Viewport(img.width(), img.height(), -1,1,-1,1);
	//Shader * shader = new FlatShader();
	Shader * shader = new BlinnPhongShader();
	shader->setGlobalLight(Color(1.0,1.0,1));
	
	RayTracer rt(camera,viewport,projection, shader);

	rt.setBackgroundColor(Color(0.0,0.0,0));
	if(rt.valid()){
		rt.render(scene, img, depth);
		Image::exportPPM(outfile, img);	
	}
	delete shader;
	delete camera;
	delete projection;
	delete viewport;

}



