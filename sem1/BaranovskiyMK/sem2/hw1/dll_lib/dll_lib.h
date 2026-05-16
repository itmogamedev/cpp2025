#ifndef DLL_LIB_H
#define DLL_LIB_H

#include<iostream>
#include<ostream>
#include<cmath>

struct Vec3{
  float x;
  float y;
  float z;
};

Vec3 operator+(Vec3 &a, Vec3 &b );
Vec3 operator*(Vec3 &a, int b);
float multyplay_v_v(Vec3 *a, Vec3 *b);
Vec3 multyplay_V_V(Vec3 *a, Vec3 *b);
float lenn(Vec3 *a);
void normalize(Vec3 *a);

std::ostream& operator<<(std::ostream &out, Vec3 &a);
#endif //DLL_LIB_H