#ifndef _VEC3_INCLUDED
#define _VEC3_INCLUDED

#include <ostream>

#define EPSILON (0.000001)

struct Vec3 {
    float x;
    float y;
    float z;
};

void add(Vec3 *a, const Vec3 *b);
void mul(Vec3 *a, float b);
void cross(Vec3 *c, const Vec3 *a, const Vec3 *b);
void normalize(Vec3 *a);

float dot(const Vec3 *a, const Vec3 *b);
float len(const Vec3 *a);

Vec3 operator+(Vec3 &left, Vec3 &right);
Vec3 operator-(Vec3 &left, Vec3 &right);
float operator*(Vec3 &left, Vec3 &right);

std::ostream& operator<<(std::ostream& os, Vec3& vec);

#endif
