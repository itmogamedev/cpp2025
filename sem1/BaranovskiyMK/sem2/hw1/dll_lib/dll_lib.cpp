#include"dll_lib.h"

Vec3 operator+(Vec3 &a, Vec3 &b ){
  float X = a.x + b.x;
  float Y = a.y + b.y;
  float Z = a.z + b.z;
  Vec3 ans = {X,Y,Z};
  return ans;
};

Vec3 operator*(Vec3 &a, int b){
  float X = a.x * b;
  float Y = a.y * b;
  float Z = a.z * b;
  Vec3 ans = {X,Y,Z};
  return ans;
};

float multyplay_v_v(Vec3 *a, Vec3 *b){
  return a->x * b->x + a->y * b->y + a->z * b->z;
};

Vec3 multyplay_V_V(Vec3 *a, Vec3 *b){
  float X = a->y * b->z - b->y * a->z;
  float Y = a->x * b->z - b->x * a->z;
  float Z = a->x * b->y - b->x * a->y;
  Vec3 ans = {X,Y,Z};
  return ans;
};

float lenn(Vec3 *a){
  return sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
};

void normalize(Vec3 *a){
  float l = lenn(a);
  a->x /= l;
  a->y /= l;
  a->z /= l;
};

std::ostream& operator<<(std::ostream& os, Vec3& vec) {
  os << "{" << vec.x << "," << vec.y << "," << vec.z << "}";
  return os;
};

