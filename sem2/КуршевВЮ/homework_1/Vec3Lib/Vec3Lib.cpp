#include "pch.h"
#include "Vec3Lib.h"

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

Vec3 add(const Vec3& vector_a, const Vec3& vector_b) {
    return vector_a + vector_b;
}

Vec3 subtract(const Vec3& vector_a, const Vec3& vector_b) {
    return vector_a - vector_b;
}

Vec3 multiply(const Vec3& vector, double scalar) {
    return vector * scalar;
}

double scalMult(const Vec3& vector_a, const Vec3& vector_b) {
    return vector_a.x * vector_b.x + vector_a.y * vector_b.y + vector_a.z * vector_b.z;
}

Vec3 vectMult(const Vec3& vector_a, const Vec3& vector_b) {
    return Vec3(
        vector_a.y * vector_b.z - vector_a.z * vector_b.y,
        vector_a.z * vector_b.x - vector_a.x * vector_b.z,
        vector_a.x * vector_b.y - vector_a.y * vector_b.x
    );
}

double length(const Vec3& vector) {
    return std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

Vec3 normalize(const Vec3& vector) {
    double len = length(vector);
    if (len == 0) {
        return Vec3(0, 0, 0);
    }
    return Vec3(vector.x / len, vector.y / len, vector.z / len);
}

Vec3 operator*(double scalar, const Vec3& vector) {
    return vector * scalar;
}