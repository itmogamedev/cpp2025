#include "pch.h"
#include "vect.h"
#include <cmath>

Vec3::Vec3(double xVal, double yVal, double zVal)
	: x(xVal), y(yVal), z(zVal) {
}

Vec3 Vec3::operator+(const Vec3& a) const {
	return Vec3{ x + a.x, y + a.y, z + a.z };
}

Vec3 Vec3::operator-(const Vec3& a) const {
	return Vec3{ x - a.x, y - a.y, z - a.z };
}

double Vec3::operator*(const Vec3& a) const {
	return x * a.x + y * a.y + z * a.z;
}

Vec3 Vec3::operator*(double a) const {
	return Vec3{ a * x, a * y, a * z };
}

std::ostream& operator<<(std::ostream& os, const Vec3& v) {
	return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

Vec3 vecSum(Vec3 a, Vec3 b) {
	return a + b;
}
Vec3 vecSubtraction(Vec3 a, Vec3 b) {
	return a - b;
}
Vec3 vecScalMult(Vec3 a, double b) {
	return a * b;
}
Vec3 vecScalMult(double b, Vec3 a) {
	return a * b;
}
double scalMult(Vec3 a, Vec3 b) {
	return a * b;
}
Vec3 vecMult(Vec3 a, Vec3 b) {
	return Vec3{ a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x };
}
double lenVec(Vec3 a) {
	return std::sqrt(a * a);
}
Vec3 normVec(Vec3 a) {
	double len = lenVec(a);
	if (len == 0) return Vec3(0, 0, 0);
	return Vec3{ a.x / len, a.y / len, a.z / len };
}