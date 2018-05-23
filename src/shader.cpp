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

	//L = ka Ia + SUM(1,N) [kd Ii max(0, dot(n,l_i)) + ks Ii max(0, dot(n,h_i)^p]
	//removed to speed up, used as reference
	//notice ka and light are RGB so multiply does component-wise mult for ka and light RGB values
	Color ka = intersection.material()->ambient;
	Color kd = intersection.material()->diffuse;
	Color ks  = intersection.material()->specular;
	double p = intersection.material()->shininess; 


	Vec3f n = intersection.normal();
	Vec3f v = (camera.eye() - intersection.poi()).normal(); //from point to camera (e-p)
	Vec3f l; //from light to point (p-l)
	Vec3f h;//half between l and v
	Vec3f lightAvg;
	double shine, diffuse;
	color.fill(0);
	color += ka*_globalLight;
	for(auto const & light : scene.lights()){
		l =  (light->position() - intersection.poi()).normal();
		h = (v+l).normal();
		shine = n.dot(h);
		diffuse = n.dot(l);
		if(shine < 0) shine = 0;
		if(diffuse < 0) diffuse = 0;
		//add shade color
		color += kd  * light->color() * diffuse +  ks * light->color() * pow(shine, p);
		//lightAvg += light->color();
	}
	//lightAvg /= scene.lights().size();// avg ambient light color 
	//color += ka*lightAvg;
	if(color.r()>1)color.r() = 1;
	if(color.g()>1)color.g() = 1;
	if(color.b()>1)color.b() = 1;
}
