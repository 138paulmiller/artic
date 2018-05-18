#include "shader.hpp"


HDR FlatShader::shade(	const Camera& camera, 
						const Scene& scene, 
						const Intersection & intersection){
	if(intersection.valid())
		return intersection.object()->material()->base;
	return HDR(0);
}


HDR  BlinnPhongShader::shade(const Camera& camera, 
							const Scene& scene, 
							const Intersection & intersection){

}
