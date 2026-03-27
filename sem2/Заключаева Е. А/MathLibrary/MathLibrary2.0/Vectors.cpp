#include "pch.h"

#include "Vectors.h"

#include <iostream>

vectors::vectors(float x1, float y1, float z1) {
	x = x1;
	y = y1;
	z = z1;
}

float vectors::get_x() { return x; }
float vectors::get_y() { return y; }
float vectors::get_z() { return z; }

std::tuple<float, float, float> vectors::summary(vectors& v1, vectors& v2) {
	return std::make_tuple(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

std::tuple<float, float, float> vectors::sub(vectors& v1, vectors& v2) {
	return std::make_tuple(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

std::tuple<float, float, float> vectors::prod(int num, vectors& v1) {
	return std::make_tuple(num * v1.x, num * v1.y, num * v1.z);
}

float vectors::sc_prod(vectors& v1, vectors& v2) {
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

std::tuple<float, float, float> vectors::vec_prod(vectors& v1, vectors& v2) {
	return std::make_tuple(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

float vectors::lenght(vectors& v1) {
	return std::sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
}

std::tuple<float, float, float> vectors::normal(vectors& v1) {
	return std::make_tuple(v1.x / lenght(v1), v1.y / lenght(v1), v1.z / lenght(v1));
}

vectors operator+(vectors& v1, vectors& v2) {
	std::tuple<float, float, float> result = v1.summary(v1, v2);
	return vectors(
		std::get<0>(result),
		std::get<1>(result),
		std::get<2>(result)
	);
}

vectors operator-(vectors& v1, vectors& v2) {
	std::tuple<float, float, float> result = v1.sub(v1, v2);
	return vectors(
		std::get<0>(result),
		std::get<1>(result),
		std::get<2>(result)
	);
}

vectors operator*(int num, vectors& v1) {
	std::tuple<float, float, float> result = v1.prod(num, v1);
	return vectors(
		std::get<0>(result),
		std::get<1>(result),
		std::get<2>(result)
	);
}

std::ostream& operator<<(std::ostream& os, vectors& v1) {
	os << "(" << v1.x << ", " << v1.y << ", " << v1.z << ")";
	return os;
}