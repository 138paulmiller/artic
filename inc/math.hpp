#include <iostream>
#include <array>
#include <initializer_list>
#include <assert.h>
#include <math.h>

/*	
LInear Algebra library
*/

namespace math{
	/************************* Forward Decls ***************************/
	double epsilon = 0.001;			//variable 
	template <typename Elem_T, int Dimension>
	class Vec;
	template <typename Elem_T, int Dimension_N, int Dimension_M>
	class Mat;
	template <typename Vec_T>
	class Ray;

	/*********************************** Common Types ****************************/			
	template <typename T> using Vec2 = Vec<T, 2>;
	template <typename T> using Vec3 = Vec<T, 3>;
	template <typename T> using Mat3x3 = Mat<T, 3, 3>;
	template <typename T> using Mat4x4 = Mat<T, 4, 4>;

	using Vec2i = Vec3<int>;
	using Vec3i = Vec3<int>;
	using Vec2f = Vec3<double>;
	using Vec3f = Vec3<double>;


	/*********************************** Helper Macros  ****************************/
	#define VecType Vec<Elem_T, Dimension>
	#define MatType Mat<Elem_T, Dimension_N, Dimension_M>
	#define RayType Ray<Vec>

	//test if almost equal 
	#define ALMOST_EQUAL(a, b) (fabs(a-b) <  epsilon)


	/************************ Overloaded Friend operators **********************/
	
	template <typename Elem_T, int Dimension>
	std::ostream & operator<<(std::ostream & os, const Vec<Elem_T, Dimension> & vec);


	/*********************************** Vec ****************************/
	template <typename Elem_T, int Dimension>
	class Vec{
		private:
			std::array<Elem_T, Dimension> _elements;
		public:

			Vec(Elem_T default_value =0);
			Vec(std::initializer_list<Elem_T> ilist);
			Vec(const VecType &other);
			// Modifiers
			inline VecType operator=(const VecType & rhs);
			inline void normalize(); 
			inline void fill(Elem_T value); 
			// Accessors 
			inline Elem_T operator[](int index)const;
			inline Elem_T magnitude()const;
			inline Elem_T magnitude2()const;
			inline VecType normal()const ;
			// Binary Vector operations
			inline Elem_T dot(const VecType & rhs)const;
			inline VecType cross(const VecType & rhs)const;
			inline VecType operator+(const VecType & rhs) const;
			inline VecType operator-(const VecType & rhs)const;
			inline VecType operator*(Elem_T scalar)const;
			inline VecType operator/(Elem_T scalar)const;

			inline bool operator==(const VecType & rhs)const;
			inline bool operator!=(const VecType & rhs)const;
									
			//Friends
			template <typename _Elem_T, int _Dimension>
			friend std::ostream & operator<< (std::ostream & os, const Vec<_Elem_T, _Dimension> & vec);
			
	};

	/*********************************** Mat ****************************/
	template <typename Elem_T, int Dimension_N, int Dimension_M>
	class Mat{
		private:
			using Vec_T = Vec<Elem_T, Dimension_N>;
			std::array<Vec_T, Dimension_M> _elements;
		public:
			Mat(std::initializer_list<Vec_T> ilist);
			
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

	template <typename Elem_T, int Dimension>
	VecType::Vec(Elem_T default_value){
		for(int i =0; i < Dimension; ++i)
			_elements[i] = default_value;	
	}

	template <typename Elem_T, int Dimension>
	VecType::Vec(std::initializer_list<Elem_T> ilist){
		auto it = ilist.begin();
		for(int i =0; i < Dimension && it != ilist.end(); ++i, ++it)
			_elements[i] = *it;	

	}

	template <typename Elem_T, int Dimension>
	VecType::Vec(const Vec<Elem_T, Dimension> &other):
		_elements(other._elements){	
	}
	
	template <typename Elem_T, int Dimension>
	VecType VecType::operator=(const VecType & rhs) {
		_elements = rhs._elements;	
		return *this;
	}
	template <typename Elem_T, int Dimension>
	void VecType::normalize(){
		*this = normal();

	} 

	template <typename Elem_T, int Dimension>
	void VecType::fill(Elem_T value){
		for(auto & e : _elements)
			e = value;
	}

	template <typename Elem_T, int Dimension>
	Elem_T VecType::magnitude2()const{
		Elem_T sum = 0;
		for(auto & e : _elements)
			sum += e*e;
		return sum;
	}

	template <typename Elem_T, int Dimension>
	Elem_T VecType::magnitude()const{
		return sqrt(magnitude2());
	}

	template <typename Elem_T, int Dimension>
	VecType VecType::normal()const{
		VecType result;
		auto mag = magnitude();
		for(int i =0; i < _elements.size(); ++i)
			result[i] = _elements[i]/mag;
		return result;
	}


	template <typename Elem_T, int Dimension>
	Elem_T VecType::dot(const VecType & rhs) const{
		Elem_T sum = 0;
		for(int i =0; i < Dimension; ++i)
			sum += _elements[i] * rhs._elements[i];	
		return sum;
	}
	template <typename Elem_T, int Dimension>
	VecType VecType::cross(const VecType & rhs) const{
 		static_assert(Dimension == 3, "Cross Product defined only on Vec3");
		VecType result;
		result._elements[0] = _elements[1]*rhs._elements[2] - _elements[2]*rhs._elements[1];	
		result._elements[1] = _elements[2]*rhs._elements[0] - _elements[0]*rhs._elements[2];	
		result._elements[2] = _elements[0]*rhs._elements[1] - _elements[1]*rhs._elements[0];	
		return result;
	}			

	template <typename Elem_T, int Dimension>
	VecType VecType::operator+(const VecType & rhs) const{
		Vec<Elem_T, Dimension> result;
		for(int i =0; i < Dimension; ++i)
			result._elements[i] = _elements[i] + rhs._elements[i];	
		return result;
	}

	template <typename Elem_T, int Dimension>
	VecType VecType::operator-(const VecType & rhs)const{
		Vec<Elem_T, Dimension> result;
		for(int i =0; i < Dimension; ++i)
			result._elements[i] = _elements[i] - rhs._elements[i];	
		return result;
	}
	
	template <typename Elem_T, int Dimension>
	VecType VecType::operator*(Elem_T scalar)const{
		VecType result(*this);
		for(auto & e : result._elements)
			e = e * scalar;	
		return result;
	}
	
	template <typename Elem_T, int Dimension>
	VecType VecType::operator/(Elem_T scalar)const{
		VecType result(*this);
		for(auto & e : result._elements)
			e = e/ scalar;
		return result;
	}

	template <typename Elem_T, int Dimension>
	Elem_T VecType::operator[](int index)const{
		assert(index<Dimension && index > -1);
		return _elements[index];
	}


	
	template <typename Elem_T, int Dimension>
	bool VecType::operator==(const VecType & rhs)const{
		for(int i =0; i < Dimension; ++i)
			if(! ALMOST_EQUAL(_elements[i], rhs._elements[i]))
				return false;	
		return true;
	}
	
	template <typename Elem_T, int Dimension>
	bool VecType::operator!=(const VecType & rhs)const{
		return !(*this == rhs);
	}
							
	template <typename Elem_T, int Dimension>
	std::ostream & operator<< (std::ostream & os, const VecType & vec){
		os << "< ";
		for(int i =0; i < Dimension; ++i)
			os << vec._elements[i] << (i!=Dimension-1? ", " : " ");	
		return os << '>';
	}

};





