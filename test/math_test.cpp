
#include "math.hpp"
#define ERR(code,got, expect) {std::cout << "\nFail: " << #code\
										<< "\n\tReceived:" << got\
										<< "\n\tExpected:" << expect;}
#define PASS(code,got) {std::cout << "\nPassed: " << #code;}
#define TEST_EQ(msg, code, expect)  if(code == expect)PASS(msg, code)else ERR(msg,code,expect)
using namespace math;

int main(){
	std::cout << "\nVECTOR\n";
	Vec3f a0({1,3,5});
	Vec3f b0(a0);
	Vec3f a1 = {1,3,5};
	Vec3f b1 = a1;

	TEST_EQ("CONSTRUCTOR", a0, a0)
	TEST_EQ("ASSIGNMENT", a1, a1)
	TEST_EQ("{1, 3, 5} * 3", Vec3f({1, 3, 5})*3, Vec3f({3, 9, 15}))
	TEST_EQ("{1, 3, 5} / 2", Vec3f({1, 3, 5})/2, Vec3f({0.5, 1.5, 2.5}))
	TEST_EQ("{1, 3, 5} + {2, 4, 6}", Vec3f({1, 3, 5}) + Vec3f({2, 4, 6}), Vec3f({3, 7, 11}))
	TEST_EQ("{1, 3, 5} - {2, 4, 6}", Vec3f({1, 3, 5}) - Vec3f({2, 4, 6}), Vec3f({-1 ,-1,-1}))
	TEST_EQ("{1, 3, 5} x {2, 4, 6}", Vec3f({1, 3, 5}).cross(Vec3f({2, 4, 6})), Vec3f({-2 ,4,-2}))
	TEST_EQ("{1, 3, 5} . {2, 4, 6}", Vec3f({1, 3, 5}).dot(Vec3f({2, 4, 6})), 44 )


	TEST_EQ("{0.1, 34, -5.2} * 3", Vec3f({0.1, 34, -5.2})*3, Vec3f({0.3, 102, -15.6}))
	TEST_EQ("{0.1, 34, -5.2} / 2", Vec3f({0.1, 34, -5.2})/2, Vec3f({0.05, 17, -2.6}))
	TEST_EQ("{0.1, 34, -5.2} + {-2, 14, 6}", Vec3f({0.1, 34, -5.2}) + Vec3f({-2, 14, 6}), Vec3f({-1.9, 48, 0.8}))
	TEST_EQ("{0.1, 34, -5.2} - {-2, 14, 6}", Vec3f({0.1, 34, -5.2}) - Vec3f({-2, 14, 6}), Vec3f({2.1, 20, -11.2}))
	TEST_EQ("{0.1, 34, -5.2} x {-2, 14, 6}", Vec3f({0.1, 34, -5.2}).cross(Vec3f({-2, 14, 6})), Vec3f({276.8, 9.8, 69.4}))
	TEST_EQ("{0.1, 34, -5.2} . {-2, 14, 6}", Vec3f({0.1, 34, -5.2}).dot(Vec3f({-2, 14, 6})), 444.6 )


	std::cout << "\nDONE\n";
}