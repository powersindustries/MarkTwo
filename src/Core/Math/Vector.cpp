#include "Vector.h"
#include <math.h>

namespace CoreMath
{


// ------------------------------------------------------------
// ------------------------------------------------------------
Vector2f VectorMethods::Add(Vector2f* vector1, Vector2f* vector2)
{
    Vector2f newVector;
    newVector.m_fX = vector1->m_fX + vector2->m_fX;
    newVector.m_fY = vector1->m_fY + vector2->m_fY;

    return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vector3f VectorMethods::Add(Vector3f* vector1, Vector3f* vector2)
{
    Vector3f newVector;
    newVector.m_fX = vector1->m_fX + vector2->m_fX;
    newVector.m_fY = vector1->m_fY + vector2->m_fY;
    newVector.m_fZ = vector1->m_fZ + vector2->m_fZ;

    return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vector2i VectorMethods::Add(Vector2i* vector1, Vector2i* vector2)
{
    Vector2i newVector;
    newVector.m_iX = vector1->m_iX + vector2->m_iX;
    newVector.m_iY = vector1->m_iY + vector2->m_iY;

    return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vector3i VectorMethods::Add(Vector3i* vector1, Vector3i* vector2)
{
    Vector3i newVector;
    newVector.m_iX = vector1->m_iX + vector2->m_iX;
    newVector.m_iY = vector1->m_iY + vector2->m_iY;
    newVector.m_iZ = vector1->m_iZ + vector2->m_iZ;

    return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vector2f VectorMethods::Subtract(Vector2f* vector1, Vector2f* vector2)
{
    Vector2f newVector;
    newVector.m_fX = vector1->m_fX - vector2->m_fX;
    newVector.m_fY = vector1->m_fY - vector2->m_fY;

    return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vector3f VectorMethods::Subtract(Vector3f* vector1, Vector3f* vector2)
{
    Vector3f newVector;
    newVector.m_fX = vector1->m_fX - vector2->m_fX;
    newVector.m_fY = vector1->m_fY - vector2->m_fY;
    newVector.m_fZ = vector1->m_fZ - vector2->m_fZ;

    return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vector2i VectorMethods::Subtract(Vector2i* vector1, Vector2i* vector2)
{
    Vector2i newVector;
    newVector.m_iX = vector1->m_iX - vector2->m_iX;
    newVector.m_iY = vector1->m_iY - vector2->m_iY;

    return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vector3i VectorMethods::Subtract(Vector3i* vector1, Vector3i* vector2)
{
    Vector3i newVector;
    newVector.m_iX = vector1->m_iX - vector2->m_iX;
    newVector.m_iY = vector1->m_iY - vector2->m_iY;
    newVector.m_iZ = vector1->m_iZ - vector2->m_iZ;

    return newVector;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
Vector2f VectorMethods::ScalarMultiply(Vector2f* vector, float scalar)
{
    Vector2f newVector;
    newVector.m_fX = scalar * vector->m_fX;
    newVector.m_fY = scalar * vector->m_fY;

    return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vector3f VectorMethods::ScalarMultiply(Vector3f* vector, float scalar)
{
    Vector3f newVector;
    newVector.m_fX = scalar * vector->m_fX;
    newVector.m_fY = scalar * vector->m_fY;
    newVector.m_fZ = scalar * vector->m_fZ;

    return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vector2i VectorMethods::ScalarMultiply(Vector2i* vector, int scalar)
{
    Vector2i newVector;
    newVector.m_iX = scalar * vector->m_iX;
    newVector.m_iY = scalar * vector->m_iY;

    return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vector3i VectorMethods::ScalarMultiply(Vector3i* vector, int scalar)
{
    Vector3i newVector;
    newVector.m_iX = scalar * vector->m_iX;
    newVector.m_iY = scalar * vector->m_iY;
    newVector.m_iZ = scalar * vector->m_iZ;

    return newVector;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
Vector2f VectorMethods::ScalarDivide(Vector2f* vector, float scalar)
{
    Vector2f newVector;
    newVector.m_fX = scalar / vector->m_fX;
    newVector.m_fY = scalar / vector->m_fY;

    return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vector3f VectorMethods::ScalarDivide(Vector3f* vector, float scalar)
{
    Vector3f newVector;
    newVector.m_fX = scalar / vector->m_fX;
    newVector.m_fY = scalar / vector->m_fY;
    newVector.m_fZ = scalar / vector->m_fZ;

    return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
float VectorMethods::VectorLength(Vector2f* vector)
{
    // SquareRoot(x^2 + y^2)
    double vectorLength = sqrt((vector->m_fX * vector->m_fX) + (vector->m_fY * vector->m_fY));
    return static_cast<float>(vectorLength);
}


// ------------------------------------------------------------
// ------------------------------------------------------------
float VectorMethods::VectorLength(Vector3f* vector)
{
    // SquareRoot(x^2 + y^2 + z^2)
    double vectorLength = sqrt((vector->m_fX * vector->m_fX) + (vector->m_fY * vector->m_fY) + (vector->m_fZ * vector->m_fZ));
    return static_cast<float>(vectorLength);
}


float VectorMethods::VectorLength(Vector2i* vector)
{
    // SquareRoot(x^2 + y^2)
    double vectorLength = sqrt((vector->m_iX * vector->m_iX) + (vector->m_iY * vector->m_iY));
    return static_cast<float>(vectorLength);
}

float VectorMethods::VectorLength(Vector3i* vector)
{
    // SquareRoot(x^2 + y^2 + z^2)
    double vectorLength = sqrt((vector->m_iX * vector->m_iX) + (vector->m_iY * vector->m_iY) + (vector->m_iZ * vector->m_iZ));
    return static_cast<float>(vectorLength);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
Vector2f VectorMethods::RotateCounterClockwise(Vector2f* vector, float angleInDegrees)
{
    Vector2f newVector;
    newVector.m_fX = static_cast<float>((vector->m_fX * cos(angleInDegrees)) - (vector->m_fY * sin(angleInDegrees)));
    newVector.m_fY = static_cast<float>((vector->m_fX * sin(angleInDegrees)) + (vector->m_fY * cos(angleInDegrees)));
    return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vector3f VectorMethods::RotateAboutX(Vector3f* vector, float angleInDegrees)
{
    // Rotation Matrix About X Axis
    // 1 0 0
    // 0 cos(theta) -sin(theta)
    // 0 sin(theta) cos(theta)
    Vector3f newVector;
    newVector.m_fX = (1 * vector->m_fX) + (0 * vector->m_fY) + (0 * vector->m_fZ);
    newVector.m_fY = static_cast<float>((0 * vector->m_fX) + (cos(angleInDegrees) * vector->m_fY) + (-1 * sin(angleInDegrees) * vector->m_fZ));
    newVector.m_fZ = static_cast<float>((0 * vector->m_fX) + (sin(angleInDegrees) * vector->m_fY) + (0 * cos(angleInDegrees) * vector->m_fZ));

    return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vector3f VectorMethods::RotateAboutY(Vector3f* vector, float angleInDegrees)
{
    // Rotation Matrix about Y Axis
    // cos(theta) 0 sin(theta)
    // 0 1 0
    // -sin(theta) cos(theta) 0
    Vector3f newVector;
    newVector.m_fX = static_cast<float>((cos(angleInDegrees) * vector->m_fX) + (0 * vector->m_fY) + (sin(angleInDegrees) * vector->m_fZ));
    newVector.m_fY = (0 * vector->m_fX) + (1 * vector->m_fY) + (0 * vector->m_fZ);
    newVector.m_fZ = static_cast<float>((-1 * sin(angleInDegrees) * vector->m_fX) + (cos(angleInDegrees) * vector->m_fY) + (0 * vector->m_fZ));

    return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vector3f VectorMethods::RotateAboutZ(Vector3f* vector, float angleInDegrees)
{
    // Rotation Matrix about Z Axis
    // cos(theta) -sin(theta) 0
    // sin(theta) cos(theta) 0
    // 0 0 1
    Vector3f newVector;
    newVector.m_fX = static_cast<float>((cos(angleInDegrees) * vector->m_fX) + (-1 * sin(angleInDegrees) * vector->m_fY) + (0 * vector->m_fZ));
    newVector.m_fY = static_cast<float>((sin(angleInDegrees) * vector->m_fX) + (cos(angleInDegrees) * vector->m_fY) + (0 * vector->m_fZ));
    newVector.m_fZ = (0 * vector->m_fX) + (0 * vector->m_fY) + (1 * vector->m_fZ);

    return newVector;
}


float VectorMethods::AnglesBetweenVector2InDegrees(Vector2f* vector1, Vector2f* vector2)
{
    // Angle = Cos-1( dot product(vector1 Vector2f) / ||vector1|| ||Vector2f||
    // Angle = Cos-1(dot product / length)
    
    float numerator = DotProduct(vector1, vector2);
    float denominator = VectorLength(vector1) * VectorLength(vector2);

    return static_cast<float>(acos(numerator / denominator));
}


// ------------------------------------------------------------
// ------------------------------------------------------------
float VectorMethods::DotProduct(Vector2f* vector1, Vector2f* vector2)
{
    float dotProduct = (vector1->m_fX * vector2->m_fX) + (vector1->m_fY * vector2->m_fY);
    return dotProduct;
}

bool VectorMethods::ArePerpendicular(Vector2f* vector1, Vector2f* vector2)
{
    return DotProduct(vector1, vector2) == 0;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vector3f VectorMethods::CrossProduct(Vector3f* vector1, Vector3f* Vector2f)
{
    //          [v1y * v2z - v1z * v2y ]
    // Returns: [v1x * v2x - v1x * v2z ]
    //          [v1z * v2y - v1y * v2x ]
    Vector3f newVector;
    newVector.m_fX = (vector1->m_fY * Vector2f->m_fZ) - (vector1->m_fZ * Vector2f->m_fY);
    newVector.m_fY = (vector1->m_fY * Vector2f->m_fZ) - (vector1->m_fX * Vector2f->m_fZ);
    newVector.m_fZ = (vector1->m_fY * Vector2f->m_fZ) - (vector1->m_fY * Vector2f->m_fX);

    return newVector;
}

}