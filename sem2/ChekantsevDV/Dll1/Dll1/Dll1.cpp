#include "pch.h"
#include "Dll1.h"

Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

Vec3 Vec3::operator+(const Vec3& other) const {
    return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator-(const Vec3& other) const {
    return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator*(double scalar) const {
    return Vec3(x * scalar, y * scalar, z * scalar);
}

std::ostream& operator<<(std::ostream& os, const Vec3& vector) {
    os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
    return os;
}

Vec3 operator*(double scalar, const Vec3& vector) {
    return vector * scalar;
}

Vec3 add(const Vec3& a, const Vec3& b) {
    return a + b;
}

Vec3 subtract(const Vec3& a, const Vec3& b) {
    return a - b;
}

Vec3 multiply(const Vec3& vector, double scalar) {
    return vector * scalar;
}

double multiplyScalar(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 multiplyVector(const Vec3& a, const Vec3& b) {
    return Vec3(a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x);
}

double length(const Vec3& vector) {
    return std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

Vec3 normalize(const Vec3& vector) {
    double len = length(vector);
    if (len == 0) return Vec3(0, 0, 0);
    return Vec3(vector.x / len, vector.y / len, vector.z / len);
}