#include "shader.hpp"


Vec3f FlatShader::shade(	const Camera& camera, 
						const Scene& scene, 
						const Intersection & intersection){
	if(intersection.valid()) //objects not null
		return intersection.material()->ambient;
	return Vec3f(0);
}


Vec3f  BlinnPhongShader::shade(const Camera& camera, 
							const Scene& scene, 
							const Intersection & intersection){

	//

}
