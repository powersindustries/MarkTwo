#pragma once

namespace MarkTwo
{
    namespace Utilities
    {
        struct Vec3
        {
            float x;
            float y;
            float z;

            Vec3();
            Vec3(const float& x, const float& y, const float& z);

            Vec3& Add(const Vec3& other);
            Vec3& Subtract(const Vec3& other);
            Vec3& Multiply(const Vec3& other);
            Vec3& Divide(const Vec3& other);

            bool operator==(const Vec3& other);
            bool operator!=(const Vec3& other);

            friend Vec3 operator+(Vec3 left, const Vec3& right);
            friend Vec3 operator-(Vec3 left, const Vec3& right);
            friend Vec3 operator*(Vec3 left, const Vec3& right);
            friend Vec3 operator/(Vec3 left, const Vec3& right);

            Vec3& operator+=(const Vec3& other);
            Vec3& operator-=(const Vec3& other);
            Vec3& operator*=(const Vec3& other);
            Vec3& operator/=(const Vec3& other);

        };
    }
}

