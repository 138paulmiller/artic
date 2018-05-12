
#include "math.hpp"
#define ERR(code,got, expect) {std::cout << std::setprecision(math::precision)\
										<< "\nFail: " << #code\
										<< "\n\tReceived:" << got\
										<< "\n\tExpected:" << expect;}
#define PASS(code,got) {std::cout << "\nPassed: " << #code;}
#define TEST_EQ(msg, code, expect)  if(	code==expect )PASS(msg, code)else ERR(msg,code,expect)
#define TEST_ALMOST_EQ(msg, code, expect)  if(math::almost_equal(code, expect) )PASS(msg, code)else ERR(msg,code,expect)
using namespace math;

int main(){
	std::cout << "\nTESTING VEC\n";
	Vec3f a0({1,3,5});
	Vec3f b0(a0);
	Vec3f a1 = {1,3,5};
	Vec3f b1 = a1;

	TEST_EQ("CONSTRUCTOR", a0, b0)
	TEST_EQ("ASSIGNMENT", a1, b1)
	TEST_EQ("{1, 3, 5} * 3", Vec3f({1, 3, 5})*3, Vec3f({3, 9, 15}))
	TEST_EQ("{1, 3, 5} / 2", Vec3f({1, 3, 5})/2, Vec3f({0.5, 1.5, 2.5}))
	TEST_ALMOST_EQ("||{1, 3, 5}||", Vec3f({1, 3, 5}).magnitude(), 5.91608)
	TEST_EQ("{1, 3, 5}.normal", Vec3f({1, 3, 5}).normal(), Vec3f({0.16903, 0.50709, 0.84515}))
	TEST_EQ("{1, 3, 5} + {2, 4, 6}", Vec3f({1, 3, 5}) + Vec3f({2, 4, 6}), Vec3f({3, 7, 11}))
	TEST_EQ("{1, 3, 5} - {2, 4, 6}", Vec3f({1, 3, 5}) - Vec3f({2, 4, 6}), Vec3f({-1 ,-1,-1}))
	TEST_EQ("{1, 3, 5} x {2, 4, 6}", Vec3f({1, 3, 5}).cross(Vec3f({2, 4, 6})), Vec3f({-2 ,4,-2}))
	TEST_ALMOST_EQ("{1, 3, 5} . {2, 4, 6}", Vec3f({1, 3, 5}).dot(Vec3f({2, 4, 6})), 44 )


	TEST_EQ("{0.1, 34, -5.2} * 3", Vec3f({0.1, 34, -5.2})*3, Vec3f({0.3, 102, -15.6}))
	TEST_EQ("{0.1, 34, -5.2} / 2", Vec3f({0.1, 34, -5.2})/2, Vec3f({0.05, 17, -2.6}))
	TEST_EQ("{0.1, 34, -5.2} + {-2, 14, 6}", Vec3f({0.1, 34, -5.2}) + Vec3f({-2, 14, 6}), Vec3f({-1.9, 48, 0.8}))
	TEST_EQ("{0.1, 34, -5.2} - {-2, 14, 6}", Vec3f({0.1, 34, -5.2}) - Vec3f({-2, 14, 6}), Vec3f({2.1, 20, -11.2}))
	TEST_EQ("{0.1, 34, -5.2} x {-2, 14, 6}", Vec3f({0.1, 34, -5.2}).cross(Vec3f({-2, 14, 6})), Vec3f({276.8, 9.8, 69.4}))
	TEST_ALMOST_EQ("{0.1, 34, -5.2} . {-2, 14, 6}", Vec3f({0.1, 34, -5.2}).dot(Vec3f({-2, 14, 6})), 444.6 )

	std::cout << "\n\nTESTING MAT\n";
	Mat3x3i m0({
		1,2,3,
		4,5,6,
		7,8,9
	});

	Mat3x3i m1(m0);

	Mat3x3i m2({
		-1,2,3,
		4,-5,6,
		7,8,-9
	});

	Mat3x3i m3 = m2;
	Mat<int, 3, 4> m3x4 = {
		1,	2,	3,	4,
		5,	6,	7,	8,
		9,	10,	11,	12,
	};

	Mat<int, 3, 4> res = {
		36,	 40, 44,  48,
		33,	 38, 43,  48,
		-34,-28, -22, -16
	};
	auto mul = m2*m3x4;
	std:: cout << mul << "\n" << res;
	TEST_EQ("CONSTRUCTOR", m0, m1)
	TEST_EQ("ASSIGNMENT", m2, m3)
	TEST_EQ("ROW 1", m3x4.row(1), Vec4i({5, 6, 7, 8}))
	TEST_EQ("COL 1", m3x4.col(1), Vec3i({2, 6, 10}))
	TEST_EQ("MATRIX MULT", mul, res)
	


	std::cout << "\n\nDONE\n\n";
}