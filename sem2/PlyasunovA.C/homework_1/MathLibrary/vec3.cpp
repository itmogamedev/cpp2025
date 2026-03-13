#include "pch.h"
#include "vec3.h"
#include <cmath>

namespace math {

    Vec3::Vec3() : x(0.0), y(0.0), z(0.0) {}

    Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

    Vec3::Vec3(const Vec3& other) : x(other.x), y(other.y), z(other.z) {}

    Vec3& Vec3::operator=(const Vec3& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            z = other.z;
        }
        return *this;
    }

    Vec3 add(const Vec3& a, const Vec3& b) {
        return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
    }

    Vec3 subtract(const Vec3& a, const Vec3& b) {
        return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
    }

    Vec3 multiply(const Vec3& v, double scalar) {
        return Vec3(v.x * scalar, v.y * scalar, v.z * scalar);
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
        if (len > 0.0) {
            return multiply(v, 1.0 / len);
        }
        return Vec3(0.0, 0.0, 0.0);
    }

    Vec3 operator+(const Vec3& a, const Vec3& b) {
        return add(a, b);
    }

    Vec3 operator-(const Vec3& a, const Vec3& b) {
        return subtract(a, b);
    }

    Vec3 operator*(const Vec3& v, double scalar) {
        return multiply(v, scalar);
    }

    Vec3 operator*(double scalar, const Vec3& v) {
        return multiply(v, scalar);
    }

    std::ostream& operator<<(std::ostream& os, const Vec3& v) {
        os << "Vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }

}