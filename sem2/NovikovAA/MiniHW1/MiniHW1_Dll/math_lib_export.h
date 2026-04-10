#ifndef MATH_LIB_EXPORT_H
#define MATH_LIB_EXPORT_H

#ifdef MATHLIB_EXPORTS
#define MATHLIB_API __declspec(dllexport)
#else
#define MATHLIB_API __declspec(dllimport)
#endif

#endif
