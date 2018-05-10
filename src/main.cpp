#include "math.hpp"

int main(){
	math::Vec3<double>  a({1,3,4});
	math::Vec3<double>  b({1,-23,4.3});
	math::Vec3<double>  c({1,23,4});
	//Mat3x3<double> * m({a,b,c});
	
	std::cout << a.dot(b);
	std::cout << a-b;
	std::cout << a+b;
	std::cout << (a/2);
	std::cout << (a*3);
	std::cout << (c=a);

}
