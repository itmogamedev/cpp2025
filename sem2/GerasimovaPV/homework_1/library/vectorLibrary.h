//
// Created by Admin on 08.03.2026.
//
#include <ostream>
#ifdef VECTORLIBRARY_EXPORTS
#define VECTORLIBRARY_API __declspec(dllexport)
#pragma once
#else
#define VECTORLIBRARY_API __declspec(dllimport)
#endif



struct VECTORLIBRARY_API Vec3 {
  float x, y, z;
};
VECTORLIBRARY_API Vec3 operator+(const Vec3& a, const Vec3& b);

VECTORLIBRARY_API Vec3 operator-(const Vec3& a, const Vec3& b);

VECTORLIBRARY_API Vec3 operator*(const Vec3& a, float scalar);

VECTORLIBRARY_API float dot(const Vec3& a, const Vec3& b);

VECTORLIBRARY_API Vec3 cross(const Vec3& a, const Vec3& b);

VECTORLIBRARY_API float length(const Vec3& v);

VECTORLIBRARY_API Vec3 norm(const Vec3& v);

VECTORLIBRARY_API std::ostream& operator<<(std::ostream& os, const Vec3& v);

#ifndef LIBRARY_VECTORLIBRARY_H
#define LIBRARY_VECTORLIBRARY_H

#endif //LIBRARY_VECTORLIBRARY_H