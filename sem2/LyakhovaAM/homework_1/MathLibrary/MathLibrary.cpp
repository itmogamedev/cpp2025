#include "pch.h"

#include "MathLibrary.h"

Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

Vec3 Vec3::addVec(Vec3 a) {
	return Vec3(x + a.x, y + a.y, z + a.z);
}

Vec3 Vec3::subVec(Vec3 a) {
	return Vec3(x - a.x, y - a.y, z - a.z);
}

Vec3 Vec3::multiplicVec(double scal) {
	return Vec3(x * scal, y * scal, z * scal);
}

double Vec3::dotProd(Vec3 a) {
	return (a.x * x + a.y * y + a.z * z);
}

Vec3 Vec3::crossProd(Vec3 a) {
	return Vec3(a.y * z - a.z * y, a.z * x - a.x * z, a.x * y - a.y * x);
}

double Vec3::lenVec() {
	return sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::normVec() {
	double len = lenVec();
	if (len) return Vec3(x / len, y / len, z / len);
	return *this;
}

Vec3 Vec3::operator+(const Vec3& a) { return addVec(a); }
Vec3 Vec3::operator-(const Vec3& a) { return subVec(a); }
double Vec3::operator*(const Vec3& a) { return dotProd(a); }
Vec3 Vec3::operator*(const double& a) { return multiplicVec(a); }

std::ostream& operator<<(std::ostream& os, const Vec3& a) {
	std::cout << '(' << a.x << "; " << a.y << "; " << a.z << ')';
	return os;
}