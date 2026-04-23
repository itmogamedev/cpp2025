#pragma once

#ifdef DLL1_EXPORTS
#define DLL1_API __declspec(dllexport)
#else
#define DLL1_API __declspec(dllimport)
#endif
#include <cmath>

class DLL1_API FVector {
private:
    float X;
    float Y;
    float Z;

public:
    FVector();
    FVector(float x, float y, float z);

    FVector FSum(float XOther, float YOther, float ZOther) const;
    FVector FSub(float XOther, float YOther, float ZOther) const;
    FVector FScal(float Scalar) const;

    float FMult(float XOther, float YOther, float ZOther) const;
    float FLength() const;

    float GetX() const;
    float GetY() const;
    float GetZ() const;

    void SetX(float x);
    void SetY(float y);
    void SetZ(float z);

    FVector Normalize() const;
};