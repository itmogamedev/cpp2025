#include "Vec3.h"
#include <cmath>

Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

Vec3 operator+(const Vec3& a, const Vec3& b) {
    return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3 operator-(const Vec3& a, const Vec3& b) {
    return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3 operator*(const Vec3& v, double scalar) {
    return Vec3(v.x * scalar, v.y * scalar, v.z * scalar);
}

std::ostream& operator<<(std::ostream& os, const Vec3& v) {
    os << '(' << v.x << ", " << v.y << ", " << v.z << ')';
    return os;
}

double dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 cross(const Vec3& a, const Vec3& b) {
    return Vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

double length(const Vec3& v) {
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vec3 normalize(const Vec3& v) {
    double len = length(v);
    if (len == 0.0) return Vec3(0, 0, 0);
    return Vec3(v.x / len, v.y / len, v.z / len);
}