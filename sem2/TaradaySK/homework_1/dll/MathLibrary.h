#pragma once

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

extern "C" {
MATHLIBRARY_API void Add(const int* a, const int* b, float* res);
MATHLIBRARY_API void Subtract(const int* a, const int* b, float* res);
MATHLIBRARY_API void Multiply(const int* a, float scalar, float* res);
MATHLIBRARY_API float Dot(const int* a, const int* b);
MATHLIBRARY_API void Cross(const int* a, const int* b, float* res);
MATHLIBRARY_API float GetLength(const int* a);
MATHLIBRARY_API void Normalize(const int* a, float* res);
}
