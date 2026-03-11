#include <cmath>
#include <iostream>
#include <string>

class Vec3 {
 private:
  double x, y, z;

 public:
  Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

  double getX() { return x; }
  double getY() { return y; }
  double getZ() { return z; }

  void setX(double x) { this->x = x; }
  void setY(double y) { this->y = y; }
  void setZ(double z) { this->z = z; }

  Vec3 sum(Vec3 other);
  Vec3 operator+(const Vec3 other) { return sum(other); }

  Vec3 minus(Vec3 other);
  Vec3 operator-(const Vec3 other) { return minus(other); }

  Vec3 scalarV(Vec3 other);
  Vec3 operator*(Vec3 other) { return scalarV(other); }

  Vec3 scalar(double scalar);

  Vec3 vec(Vec3 other);

  Vec3 norm();

  float length() { return sqrt(x * x + y * y + z * z); }

  friend std::ostream& operator<<(std::ostream& stream, Vec3& vec) {
    return stream << "(" << std::to_string(vec.x) << ", "
                  << std::to_string(vec.y) << ", " << std::to_string(vec.z)
                  << ")";
  }
};