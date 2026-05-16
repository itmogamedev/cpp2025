#pragma once

#ifdef DLL1_EXPORTS
#define DLL1_API __declspec(dllexport)
#else
#define DLL1_API __declspec(dllimport)
#endif

class DLL1_API Vec3 {
 private:
  double x, y, z;

 public:
  Vec3();
  Vec3(double x, double y, double z);

  double getX() const { return x; }
  double getY() const { return y; }
  double getZ() const { return z; }

  Vec3 Summator(const Vec3& another_vec) const;
  Vec3 Minusator(const Vec3& another_vec) const;
  Vec3 umnojatorConst(double constanta) const;
  double Scalyarnoe(const Vec3& another_vec) const;
  Vec3 Vectornoe(const Vec3& another_vec) const;
  double length() const;
  Vec3 normalizedVersion() const;
};

DLL1_API Vec3 operator*(double constanta, const Vec3& vec);

DLL1_API std::ostream& funcForOut(std::ostream& os, const Vec3& vec);
