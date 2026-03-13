#pragma once
#include <iostream>
#include <cmath>

struct Vec3
{
    float x;
    float y;
    float z;

    Vec3()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    Vec3(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

Vec3 operator+(const Vec3& a, const Vec3& b);
Vec3 operator-(const Vec3& a, const Vec3& b);
Vec3 operator*(const Vec3& v, float scalar);

float dot(const Vec3& a, const Vec3& b);
Vec3 cross(const Vec3& a, const Vec3& b);

float length(const Vec3& v);
Vec3 normalize(const Vec3& v);

std::ostream& operator<<(std::ostream& os, const Vec3& v);