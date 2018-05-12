#include <iostream>
#include <array>
#include <initializer_list>
#include <assert.h>
#include <math.h>
#include <iomanip>

/*	
Linear Algebra library
*/


namespace math{
	/************************* Forward Decls ***************************/
	long precision = 10;			//variable 
	double epsilon = 0.1f;			 
	template <typename ELEM_T, int DIM>
	class Vec;
	template <typename ELEM_T, int DIM_H, int DIM_W>
	class Mat;
	template <typename Vec_T>
	class Ray;

	/*********************************** Common Types ****************************/			
	template <typename T> using Vec2 = Vec<T, 2>;
	template <typename T> using Vec3 = Vec<T, 3>;
	template <typename T> using Vec4 = Vec<T, 4>;
	template <typename T> using Mat2x2 = Mat<T, 3, 3>;
	template <typename T> using Mat3x3 = Mat<T, 3, 3>;
	template <typename T> using Mat4x4 = Mat<T, 4, 4>;

	using Vec2i = Vec2<int>;
	using Vec2f = Vec2<float>;

	using Vec3i = Vec3<int>;
	using Vec3f = Vec3<float>;

	using Vec4i = Vec4<int>;
	using Vec4f = Vec4<float>;

	using Mat3x3i = Mat3x3<int>;
	using Mat3x3f = Mat3x3<float>;

	using Mat4x4i = Mat4x4<int>;
	using Mat4x4f = Mat4x4<float>;
	

	/*********************************** Helper Macros  ****************************/
	#define VEC_TYPE Vec<ELEM_T, DIM>
	#define MAT_TYPE Mat<ELEM_T, DIM_H, DIM_W>
	#define RAY_TYPE Ray<Vec>

	//test if almost equal 
	inline bool almost_equal(double a, double b){ return fabs(b-a) < epsilon; }

	/************************ Overloaded Friend operators **********************/
	
	template <typename ELEM_T, int DIM>
	std::ostream & operator<<(std::ostream & os, const VEC_TYPE & vec);

	template <typename ELEM_T, int DIM_H, int DIM_W>
	std::ostream& operator<<(std::ostream & oss, const MAT_TYPE& mat);



	/*********************************** Vec ****************************/
	template <typename ELEM_T, int DIM>
	class Vec{
		private:
			std::array<ELEM_T, DIM> _elements;
		public:

			Vec(ELEM_T value =0);
			Vec(std::initializer_list<ELEM_T> ilist);
			Vec(const VEC_TYPE &other);
	
			// Accessors 
			inline ELEM_T& operator[](int index);
			inline const ELEM_T& operator[](int index)const ;
			inline ELEM_T magnitude()const;
			inline ELEM_T magnitude2()const;
			inline VEC_TYPE normal()const ;
			// Modifiers
			inline VEC_TYPE operator=(const VEC_TYPE & rhs);
			inline void normalize(); 
			inline void fill(ELEM_T value); 
			// Binary Vector operations
			inline ELEM_T dot(const VEC_TYPE & rhs)const;
			inline VEC_TYPE cross(const VEC_TYPE & rhs)const;
			inline VEC_TYPE operator+(const VEC_TYPE & rhs) const;
			inline VEC_TYPE operator-(const VEC_TYPE & rhs)const;
			inline VEC_TYPE operator*(ELEM_T scalar)const;
			inline VEC_TYPE operator/(ELEM_T scalar)const;

			inline bool operator==(const VEC_TYPE & rhs)const;
			inline bool operator!=(const VEC_TYPE & rhs)const;
									
			//Friends
			template <typename _ELEM_T, int _DIM>
			friend std::ostream & operator<< (std::ostream & os, const Vec<_ELEM_T, _DIM> & vec);
	};

	/*********************************** Mat ****************************/
	template <typename ELEM_T, int DIM_H, int DIM_W>
	class Mat{
		/*
			Mat<int, M,N> has M rows and N columns.
		*/
		private:
			using Vec_T = Vec<ELEM_T, DIM_W>;
			std::array<Vec_T, DIM_H> _elements;
		public:
			Mat(ELEM_T value=0);
			Mat(std::initializer_list<ELEM_T> ilist);
			Mat(const MAT_TYPE & other);

			inline MAT_TYPE operator=(const MAT_TYPE & rhs ); 

			inline Vec<ELEM_T, DIM_W> row(const int & i)const;
			inline Vec<ELEM_T, DIM_H> col(const int & j)const;

			inline void fill(ELEM_T value);

			inline bool operator==(const MAT_TYPE & rhs );
			inline bool operator!=(const MAT_TYPE & rhs );
			inline Vec_T& operator[](const int &index);
			inline const Vec_T& operator[](const int &index)const;

			inline bool isSquare() const;

			template <int RESULT_W> 
			inline Mat<ELEM_T, DIM_H, RESULT_W> operator*(Mat<ELEM_T, DIM_W, RESULT_W> rhs)const;

			template <typename _ELEM_T, int _DIM_H, int _DIM_W>
			friend std::ostream& operator<<(std::ostream & oss, 
								const Mat<_ELEM_T, _DIM_H, _DIM_W> & mat);			
	};

	/*********************************** Ray ****************************/
	template <typename Vec_T>
	class Ray{
		private:
			Vec_T origin, dir;
		public:
			Ray(const Vec_T &origin, const Vec_T & dir);
	};

/*********************************** Vec Definitions ****************************/

	template <typename ELEM_T, int DIM>
	VEC_TYPE::Vec(ELEM_T value){
		fill(value);	
	}

	template <typename ELEM_T, int DIM>
	VEC_TYPE::Vec(std::initializer_list<ELEM_T> ilist){
		auto it = ilist.begin();
		for(int i =0; i < DIM && it != ilist.end(); ++i, ++it)
			_elements[i] = *it;	

	}

	template <typename ELEM_T, int DIM>
	VEC_TYPE::Vec(const Vec<ELEM_T, DIM> &other):
		_elements(other._elements){	
	}

	template <typename ELEM_T, int DIM>
	ELEM_T& VEC_TYPE::operator[](int index){
		assert(index<DIM && index > -1);
		return _elements[index];
	}


	template <typename ELEM_T, int DIM>
	const ELEM_T& VEC_TYPE::operator[](int index)const {
		assert(index<DIM && index > -1);
		return _elements[index];
	}

	template <typename ELEM_T, int DIM>
	VEC_TYPE VEC_TYPE::operator=(const VEC_TYPE & rhs) {
		_elements = rhs._elements;	
		return *this;
	}
	template <typename ELEM_T, int DIM>
	void VEC_TYPE::normalize(){
		*this = normal();

	} 

	template <typename ELEM_T, int DIM>
	void VEC_TYPE::fill(ELEM_T value){
		for(auto & e : _elements)
			e = value;
	}

	template <typename ELEM_T, int DIM>
	ELEM_T VEC_TYPE::magnitude2()const{
		ELEM_T sum = 0;
		for(auto & e : _elements)
			sum += e*e;
		return sum;
	}

	template <typename ELEM_T, int DIM>
	ELEM_T VEC_TYPE::magnitude()const{
		return sqrt(magnitude2());
	}

	template <typename ELEM_T, int DIM>
	VEC_TYPE VEC_TYPE::normal()const{
		VEC_TYPE result;
		auto mag = magnitude();
		for(int i =0; i < _elements.size(); ++i)
			result[i] = _elements[i]/mag;
		return result;
	}


	template <typename ELEM_T, int DIM>
	ELEM_T VEC_TYPE::dot(const VEC_TYPE & rhs) const{
		ELEM_T sum = 0;
		for(int i =0; i < DIM; ++i)
			sum += _elements[i] * rhs._elements[i];	
		return sum;
	}
	template <typename ELEM_T, int DIM>
	VEC_TYPE VEC_TYPE::cross(const VEC_TYPE & rhs) const{
 		static_assert(DIM == 3, "Cross Product defined only on Vec3");
		VEC_TYPE result;
		result._elements[0] = _elements[1]*rhs._elements[2] - _elements[2]*rhs._elements[1];	
		result._elements[1] = _elements[2]*rhs._elements[0] - _elements[0]*rhs._elements[2];	
		result._elements[2] = _elements[0]*rhs._elements[1] - _elements[1]*rhs._elements[0];	
		return result;
	}			

	template <typename ELEM_T, int DIM>
	VEC_TYPE VEC_TYPE::operator+(const VEC_TYPE & rhs) const{
		Vec<ELEM_T, DIM> result;
		for(int i =0; i < DIM; ++i)
			result._elements[i] = _elements[i] + rhs._elements[i];	
		return result;
	}

	template <typename ELEM_T, int DIM>
	VEC_TYPE VEC_TYPE::operator-(const VEC_TYPE & rhs)const{
		Vec<ELEM_T, DIM> result;
		for(int i =0; i < DIM; ++i)
			result._elements[i] = _elements[i] - rhs._elements[i];	
		return result;
	}
	
	template <typename ELEM_T, int DIM>
	VEC_TYPE VEC_TYPE::operator*(ELEM_T scalar)const{
		VEC_TYPE result(*this);
		for(auto & e : result._elements)
			e = e * scalar;	
		return result;
	}
	
	template <typename ELEM_T, int DIM>
	VEC_TYPE VEC_TYPE::operator/(ELEM_T scalar)const{
		VEC_TYPE result(*this);
		for(auto & e : result._elements)
			e = e/ scalar;
		return result;
	}
	
	template <typename ELEM_T, int DIM>
	bool VEC_TYPE::operator==(const VEC_TYPE & rhs)const{
		for(int i =0; i < DIM; ++i)
			if(! almost_equal(_elements[i], rhs._elements[i]))
				return false;	
		return true;
	}
	
	template <typename ELEM_T, int DIM>
	bool VEC_TYPE::operator!=(const VEC_TYPE & rhs)const{
		return !(*this == rhs);
	}
							
	template <typename ELEM_T, int DIM>
	std::ostream & operator<< (std::ostream & os, const VEC_TYPE & vec){
		os << "< ";
		for(int i =0; i < DIM; ++i)
			os <<std::setprecision(precision)<< vec._elements[i] << (i!=DIM-1? ", " : " ");	
		return os << '>';
	}
/*************************** Mat Defintions **************************************************/

	template <typename ELEM_T, int DIM_H, int DIM_W>
	MAT_TYPE::Mat(ELEM_T value){
		fill(value);
	}

	template <typename ELEM_T, int DIM_H, int DIM_W>
	MAT_TYPE::Mat(std::initializer_list<ELEM_T> ilist){
		/*
			{ 0 1 ... N	 }
			| M 1 ... NxM|
		*/
		auto it = ilist.begin();
		for(int i =0; i < DIM_H ; ++i)
		 	for(int j=0; j < DIM_W && it != ilist.end(); ++j)
		 		_elements[i][j] = *(it++);					
	}

	template <typename ELEM_T, int DIM_H, int DIM_W>
	MAT_TYPE::Mat(const MAT_TYPE & other){
		for(int i =0; i < DIM_H ; ++i){
			_elements[i] = other._elements[i];					
		}
	}
	template <typename ELEM_T, int DIM_H, int DIM_W>
	MAT_TYPE MAT_TYPE::operator=(const MAT_TYPE & rhs ){
		for(int i =0; i < DIM_H ; ++i){
			_elements[i] = rhs._elements[i];					
		}
	} 

	template <typename ELEM_T, int DIM_H, int DIM_W>
	typename MAT_TYPE::Vec_T& MAT_TYPE::operator[](const int &index){
		assert(index > -1 && index < DIM_H);
		return _elements[index];
	}

	template <typename ELEM_T, int DIM_H, int DIM_W>
	const typename MAT_TYPE::Vec_T& MAT_TYPE::operator[](const int & index)const{
		assert(index > -1 && index < DIM_H);
		return _elements[index];
	}

	template <typename ELEM_T, int DIM_H, int DIM_W>
	void MAT_TYPE::fill(ELEM_T value){
		for(int i =0; i < DIM_H ; ++i)
	 		_elements[i].fill(0);					
	}

	
	template <typename ELEM_T, int DIM_H, int DIM_W>
	bool MAT_TYPE::isSquare()const{
		return DIM_W == DIM_H;
	}

	template <typename ELEM_T, int DIM_H, int DIM_W>
	bool MAT_TYPE::operator==(const MAT_TYPE & rhs ){
		for(int i =0; i < DIM_H ; ++i)
			if(_elements[i] != rhs._elements[i]) 
				return false;					
		return true;
	} 

	template <typename ELEM_T, int DIM_H, int DIM_W>
	bool MAT_TYPE::operator!=(const MAT_TYPE & rhs ){
		return !(*this == rhs);
	} 

	template <typename ELEM_T, int DIM_H, int DIM_W>
	template <int RESULT_W> Mat<ELEM_T, DIM_H, RESULT_W>
	MAT_TYPE::operator*(Mat<ELEM_T, DIM_W, RESULT_W> rhs)const{
		// if A is an n × m matrix and B is an m × p matrix, their matrix product AB is an n × p
		Mat<ELEM_T, DIM_H, RESULT_W> result(0);
		for(int i =0; i < DIM_H; ++i){
			for(int j =0; j < RESULT_W; ++j){
				result[i][j] = row(i).dot(rhs.col(j));
			}
		}
		return result;
	}

	template <typename ELEM_T, int DIM_H, int DIM_W>
	Vec<ELEM_T, DIM_W> MAT_TYPE::row(const int & i)const{
		//return row as vec
		return (*this)[i];
	}


	template <typename ELEM_T, int DIM_H, int DIM_W>
	Vec<ELEM_T, DIM_H> MAT_TYPE::col(const int & j)const{
		//return col as vec
		assert(j > -1 && j < DIM_W);
		Vec<ELEM_T, DIM_H> column;
		for(int i =0; i < DIM_H; ++i){
			column[i] = _elements[i][j];
		}
		return column;
	}

	template <typename ELEM_T, int DIM_H, int DIM_W>
	std::ostream& operator<<(std::ostream & oss, const MAT_TYPE& mat){
		oss << "[\n";
		for(int i =0; i < DIM_H; ++i){
	 		for(int j=0; j < DIM_W; ++j){
	 			oss << " " << mat[i][j];
	 			if(j < DIM_H-1 || i < DIM_W-1)
	 				oss << ",";
	 		}
 			oss << "\n";
	 	}
		return oss << "]";
		
	}
};	





