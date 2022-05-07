#pragma once

namespace CoreMath
{


struct Vector2f
{
    float m_fX;
    float m_fY;
};


struct Vector2i
{
    int m_iX;
    int m_iY;
};


struct Vector3f
{
    float m_fX;
    float m_fY;
    float m_fZ;
};


struct Vector3i
{
    int m_iX;
    int m_iY;
    int m_iZ;
};


class VectorMethods
{
public:

    static Vector2i Add(Vector2i* vector1, Vector2i* vector2);
    static Vector2f Add(Vector2f* vector1, Vector2f* vector2);

    static Vector3i Add(Vector3i* vector1, Vector3i* vector2);
    static Vector3f Add(Vector3f* vector1, Vector3f* vector2);

    static Vector2i Subtract(Vector2i* vector1, Vector2i* vector2);
    static Vector2f Subtract(Vector2f* vector1, Vector2f* vector2);

    static Vector3i Subtract(Vector3i* vector1, Vector3i* vector2);
    static Vector3f Subtract(Vector3f* vector1, Vector3f* vector2);

    static Vector2i ScalarMultiply(Vector2i* vector, int scalar);
    static Vector2f ScalarMultiply(Vector2f* vector, float scalar);

    static Vector3i ScalarMultiply(Vector3i* vector, int scalar);
    static Vector3f ScalarMultiply(Vector3f* vector, float scalar);

    static Vector2f ScalarDivide(Vector2f* vector, float scalar);
    static Vector3f ScalarDivide(Vector3f* vector, float scalar);

    static float VectorLength(Vector2i* vector);
    static float VectorLength(Vector2f* vector);

    static float VectorLength(Vector3i* vector);
    static float VectorLength(Vector3f* vector);

    static Vector2f RotateCounterClockwise(Vector2f* vector, float angleInDegrees);

    static Vector3f RotateAboutX(Vector3f* vector, float angleInDegrees);
    static Vector3f RotateAboutY(Vector3f* vector, float angleInDegrees);
    static Vector3f RotateAboutZ(Vector3f* vector, float angleInDegrees);

    static float AnglesBetweenVector2InDegrees(Vector2f* vector1, Vector2f* vector2);

    static float DotProduct(Vector2f* vector1, Vector2f* vector2);
    static bool ArePerpendicular(Vector2f* vector1, Vector2f* vector2);

    static Vector3f CrossProduct(Vector3f* vector1, Vector3f* vector2);
};

}
