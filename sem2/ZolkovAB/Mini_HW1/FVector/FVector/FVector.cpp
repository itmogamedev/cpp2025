#include "pch.h"
#include "FVector.h"

FVector::FVector()
{
    X = 0;
    Y = 0;
    Z = 0;
}

FVector::FVector(float x, float y, float z)
{
    X = x;
    Y = y;
    Z = z;
}

FVector FVector::FSum(float XOther, float YOther, float ZOther) const
{
    return FVector(X + XOther, Y + YOther, Z + ZOther);
}

FVector FVector::FSub(float XOther, float YOther, float ZOther) const
{
    return FVector(X - XOther, Y - YOther, Z - ZOther);
}

FVector FVector::FScal(float Scalar) const
{
    return FVector(X * Scalar, Y * Scalar, Z * Scalar);
}

float FVector::FMult(float XOther, float YOther, float ZOther) const
{
    return X * XOther + Y * YOther + Z * ZOther;
}

float FVector::FLength() const
{
    return std::sqrt(X * X + Y * Y + Z * Z);
}

float FVector::GetX() const
{
    return X;
}

float FVector::GetY() const
{
    return Y;
}

float FVector::GetZ() const
{
    return Z;
}

void FVector::SetX(float x)
{
    X = x;
}

void FVector::SetY(float y)
{
    Y = y;
}

void FVector::SetZ(float z)
{
    Z = z;
}

FVector FVector::Normalize() const
{
    float Len = FLength();

    if (Len == 0.0f)
    {
        return FVector(0, 0, 0);
    }

    return FVector(X / Len, Y / Len, Z / Len);
}

