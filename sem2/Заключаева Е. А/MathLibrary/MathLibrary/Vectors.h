#pragma once

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

#include <tuple>
#include <cmath>
#include <iostream>

MATHLIBRARY_API class vectors {
private:
	 float x, y, z;
	
public:
	vectors(float x1, float y1, float z1);

	float get_x();
	float get_y();
	float get_z();

	std::tuple<float, float, float> summary(vectors& v1, vectors& v2);
	std::tuple<float, float, float> sub(vectors& v1, vectors& v2);
	std::tuple<float, float, float> prod(int num, vectors& v1);
	float sc_prod(vectors& v1, vectors& v2);
	std::tuple <float,float,float> vec_prod(vectors& v1, vectors& v2);
	float lenght(vectors& v1);
	std::tuple<float, float, float> normal(vectors& v1);
	friend std::ostream& operator<<(std::ostream& os, vectors& v1) {
		os << "(" << v1.x << ", " << v1.y << ", " << v1.z << ")";
		return os;
	}
};


MATHLIBRARY_API vectors operator+(vectors& v1, vectors& v2);
MATHLIBRARY_API vectors operator-(vectors& v1, vectors& v2);
MATHLIBRARY_API vectors operator*(int num,vectors& v1);