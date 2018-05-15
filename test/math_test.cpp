
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

	Mat<int, 4, 3> m4x3 = {
		1,	5,  9,
		2,	6,	10,
		3,	7,	11,
		4,	8,	12
	};


	Mat<int, 3, 4> res = {
		36,	 40, 44,  48,
		33,	 38, 43,  48,
		-34,-28, -22, -16
	};
	Mat<int, 3, 2> m3x2 = {
		1,	2,  
		3,	4,	
		5,	6,	
	};
	Mat<int, 2, 3> m2x3 = {
		1,	3, 5,  
		2,	4, 6,	
	};

	Mat<int, 2, 3> m2x3_d = {
		2,	6, 10,  
		4,	8, 12,	
	};

	Mat<int, 4, 3> m4x3_n = {
		-1,	-5,  -9,
		-2,	-6,	-10,
		-3,	-7,	-11,
		-4,	-8,	-12
	};

	Mat<int, 4, 3> m4x3_z = {
		0,	0,  0,
		0,	0,	0,
		0,	0,	0,
		0,	0,	0
	};
	Mat<int, 2,2> m2x2 = {
		4, 6, 
		3, 8
	};
 	Mat<int, 3,3>  m3x3= {
 		0, 1, 2, 
 		3, 4, 5, 
 		6, 7, 8
 	};
 	Mat<int, 3,3>  m3x3_2= {
 		6, 1, 1, 
 		4, -2, 5, 
 		2, 8, 7
 	};
 	Mat<int, 4,4>  m4x4_g= {
 		0, 1, 2, 0,
 		3, 4, 5, 0,
 		6, 7, 8, 0,
 		0, 0, 0, 0
 	};
 	 Mat<int, 5,4>  m5x4_g2= {
 		0, 1, 2, 0,
 		3, 4, 5, 0,
 		6, 7, 8, 0,
 		0, 0, 0, 0,
 		0, 0, 0, 0
 	};
 	 Mat<int, 2,3>  m2x3_s= {
 		4, 5, 0,
 		7, 8, 0
 	};
	Mat<int, 4,4> m3x3_g = m3x3.grow<4,4>(1,1);
	Mat<int, 5,4> m3x3_g2 = m3x3.grow<5,4>(1,2);
	Mat<int, 3,3> m3x3_s = m5x4_g2.submatrix<3,3>(0,0);
	Mat<int, 2,3> m5x4_gs = m4x4_g.submatrix<2,3>(1,1);
	TEST_EQ("CONSTRUCTOR", m0, m1)
	TEST_EQ("ASSIGNMENT", m2, m3)
	TEST_EQ("ROW 1", m3x4.row(1), Vec4i({5, 6, 7, 8}))
	TEST_EQ("COL 1", m3x4.col(1), Vec3i({2, 6, 10}))
	TEST_EQ("MATRIX NEG", -m4x3, m4x3_n)
	TEST_EQ("MATRIX ADD", (m4x3+m4x3_n), m4x3_z)
	TEST_EQ("MATRIX SUB", (m4x3-m4x3), m4x3_z)
	TEST_EQ("MATRIX SCALAR MUL", m2x3*2, m2x3_d)
	TEST_EQ("MATRIX SCALAR DIV", m2x3_d/2, m2x3)
	TEST_EQ("MATRIX TRANSPOSE", m3x2.transpose(), m2x3)
	TEST_EQ("MATRIX TRANSPOSE", m3x4.transpose(), m4x3)
	TEST_EQ("MATRIX DETERMINANT", m2x2.determinant(), 14)
	TEST_EQ("MATRIX DETERMINANT", m3x3.determinant(), 0)
	TEST_EQ("MATRIX DETERMINANT", m3x3_2.determinant(), -306)
	TEST_EQ("MATRIX GROW", m3x3_g, m4x4_g)
	TEST_EQ("MATRIX GROW", m3x3_g2, m5x4_g2)
	TEST_EQ("MATRIX SUBMATRIX", m3x3_s, m3x3)
	TEST_EQ("MATRIX SUBMATRIX", m5x4_gs, m2x3_s)

	Mat<int, 3,3> A = {
		-2, -1, -3, 
		2, -3, 1, 
		2, 0, -3
	};
	Vec3i b = {3, -13, -11};
	Vec3i x = {-4, 2, 1};

	Mat<int, 3,3> A2 = {
		0, -1, -2, 
		1, 0, 3, 
		7, 1, 1
	};
	Vec3i b2 = {-8, 2, 0};
	Vec3i x2 = {-1, 6, 1};

	Mat<int, 2,2>  A3{-2, 3, 3, -4};
	Vec2i b3= {-3, 5};
	Vec2i x3= {3, 1};

	TEST_EQ("MATRIX SOLVE LINEAR", A.solveSystem(b), x)
	TEST_EQ("MATRIX SOLVE LINEAR", A2.solveSystem(b2), x2)
	TEST_EQ("MATRIX SOLVE LINEAR", A3.solveSystem(b3), x3)







	std::cout << "\n\nDONE\n\n";
}



