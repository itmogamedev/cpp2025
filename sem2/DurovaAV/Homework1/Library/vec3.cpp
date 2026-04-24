#include "pch.h"
#include "vec3.h"
#include <cmath>

Vec3::Vec3() : x(0.0), y(0.0), z(0.0) {}

Vec3::Vec3(double x_val, double y_val, double z_val)
    : x(x_val), y(y_val), z(z_val) {
}

// сложение векторов
Vec3 Vec3::operator+(const Vec3& other) const {
    return Vec3(x + other.x, y + other.y, z + other.z);
}

// вычитание векторов
Vec3 Vec3::operator-(const Vec3& other) const {
    return Vec3(x - other.x, y - other.y, z - other.z);
}

// умножение вектора на скаляр
Vec3 Vec3::operator*(double scalar) const {
    return Vec3(x * scalar, y * scalar, z * scalar);
}

// скалярное произведение
double Vec3::dot(const Vec3& other) const {
    return x * other.x + y * other.y + z * other.z;
}

// векторное произведение
Vec3 Vec3::cross(const Vec3& other) const {
    return Vec3(y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x);
}

// вычисление длины вектора
double Vec3::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

// нормализация вектора
Vec3 Vec3::normalized() const {
    double len = length();
    if (len < 1e-9) {
        return Vec3(0.0, 0.0, 0.0);
    }
    return Vec3(x / len, y / len, z / len);
}

// умножение скаляра на вектор
Vec3 operator*(double scalar, const Vec3& vec) {
    return vec * scalar;
}

// вывод вектора
std::ostream& operator<<(std::ostream& os, const Vec3& vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}