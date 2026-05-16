#include "pch.h"
#include "Vec3.h"
#include <cmath>

Vec3::Vec3() : x(0.0), y(0.0), z(0.0) {}
Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

double Vec3::getX() const { return x; }
double Vec3::getY() const { return y; }
double Vec3::getZ() const { return z; }

double Vec3::getLength() const {
	return sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::getNormalized() const {
	double ln = getLength();
	if (ln <= 0) { return Vec3(0.0, 0.0, 0.0); }
	return Vec3(x / ln, y / ln, z / ln);
}

Vec3 Vec3::operator+(const Vec3& other) const {
	return Vec3(x + other.getX(), y + other.getY(), z + other.getZ());
}

Vec3 Vec3::operator-(const Vec3& other) const {
	return Vec3(x - other.getX(), y - other.getY(), z - other.getZ());
}

Vec3 Vec3::operator*(const double& scalar) const {
	return Vec3(x * scalar, y * scalar, z * scalar);
}

double Vec3::operator*(const Vec3& other) const {
	return x * other.getX() + y * other.getY() + z * other.getZ();
}

Vec3 Vec3::operator%(const Vec3& other) const {
	return Vec3(
		y * other.getZ() - z * other.getY(),
		z * other.getX() - x * other.getZ(),
		x * other.getY() - y * other.getX()
	);
}

Vec3 operator*(const double& scalar, const Vec3& vec) {
	return vec * scalar;
}

inline std::ostream& operator<<(std::ostream& os, const Vec3& vec) {
	os << "(" 
		<< vec.getX() << ", "
		<< vec.getY() << ", "
		<< vec.getZ() << ")";
	return os;
}