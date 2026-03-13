#include "pch.h"     
#include "Vec3.h"

// Конструктор
Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

// Сложение
Vec3 Vec3::operator+(const Vec3& other) const {
    return Vec3(x + other.x, y + other.y, z + other.z);
}

// Вычитание
Vec3 Vec3::operator-(const Vec3& other) const {
    return Vec3(x - other.x, y - other.y, z - other.z);
}

// Умножение на скаляр (вектор * число)
Vec3 Vec3::operator*(double scalar) const {
    return Vec3(x * scalar, y * scalar, z * scalar);
}

// Число * вектор
Vec3 operator*(double scalar, const Vec3& v) {
    return v * scalar;  // используем уже определённый оператор
}

// Вывод в поток
std::ostream& operator<<(std::ostream& os, const Vec3& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

// Длина вектора
double Vec3::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

// Нормализация
void Vec3::normalize() {
    double len = length();
    if (len > 1e-12) {
        x /= len;
        y /= len;
        z /= len;
    }
}

// Скалярное произведение
double dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Векторное произведение
Vec3 cross(const Vec3& a, const Vec3& b) {
    return Vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}