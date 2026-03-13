#include "pch.h"
#include "task_1.h"

Vec3::Vec3(double v1, double v2, double v3) {
	v[0] = v1;
	v[1] = v2;
	v[2] = v3;
}

Vec3 Vec3::operator+(const Vec3& other) const {
	return Vec3(v[0] + other.v[0], v[1] + other.v[1], v[2] + other.v[2]);
}

Vec3 Vec3::operator-(const Vec3& other) const {
	return Vec3(v[0] - other.v[0], v[1] - other.v[1], v[2] - other.v[2]);
}

Vec3 Vec3::operator*(double value) const {
	return Vec3(v[0] * value, v[1] * value, v[2] * value);
}
double Vec3::dotProduct(const Vec3& other) const {
	return v[0] * other.v[0] + v[1] * other.v[1] + v[2] * other.v[2];
}

Vec3 Vec3::crossProduct(const Vec3& other) const {
	return Vec3(v[1] * other.v[2] - v[2] * other.v[1],
		v[2] * other.v[0] - v[0] * other.v[2], 
		v[0] * other.v[1] - v[1] * other.v[0]);
}

double Vec3::len() const {
	return std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

Vec3 Vec3::getUnit() const {
	return Vec3(v[0] / this->len(), v[1] / this->len(), v[2] / this->len());
}

std::ostream& operator<<(std::ostream& os, const Vec3& obj) {
	os << "(" << obj.v[0] << ", " << obj.v[1] << ", " << obj.v[2] << ")";
	return os;
}