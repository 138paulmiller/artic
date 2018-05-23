#include "shader.hpp"


void FlatShader::shade(Color & color, 
						const Camera& camera, 
						const Scene& scene, 
						const Intersection & intersection){
	color = intersection.material()->ambient;	
}


void BlinnPhongShader::shade(Color & color, 
									const Camera& camera, 
									const Scene& scene, 
									const Intersection & intersection){

//L = k_a I_a + SUM(1,N) [k_d Ii max(0, dot(n,l_i)) + k_s I_i max(0, dot(n,h_i)^p]
  //k_a ambient  
  //k_d diffuse 
  //k_s specular
  // I_a - light ambient, ambient color
  // n - intersection normal
  // l - POI to light 
// h - half vec beteen view (v) and light (l) = normalize(v+l)
	color.fill(0);
	//removed to speed up, used as reference
	Color ka = intersection.material()->ambient;
	Color kd = intersection.material()->diffuse;
	Color ks  = intersection.material()->specular;
	double p = intersection.material()->shininess; 
	
	Vec3f n = intersection.normal();
	Vec3f v = (camera.eye() - intersection.poi()).normal(); //from point to camera (e-p)
	Vec3f l; //from light to point (p-l)
	Vec3f h;//half between l and v
	Vec3f  diffuse, specular, ambient;
	double shine_coeff, diffuse_coeff;
	ambient = ka;
	for(auto const & light : scene.lights()){

		l =  (light->pos()- intersection.poi()).normal();
		h = (v+l).normal();

		shine_coeff = n.dot(h);
		diffuse_coeff = n.dot(l);

		if(shine_coeff < 0) shine_coeff = 0;
		if(diffuse_coeff < 0) diffuse_coeff = 0;

 		diffuse = kd * light->diffuse() * diffuse_coeff;
 		specular = ks * light->specular() * pow(shine_coeff, p); 		
		ambient = ambient * light->ambient();
		color += diffuse + specular;
	}

	color.r() += ambient[0];
	color.g() += ambient[1];
	color.b() += ambient[2]; 

	if(color.r()>1)color.r() = 1;
	if(color.g()>1)color.g() = 1;
	if(color.b()>1)color.b() = 1;
}
