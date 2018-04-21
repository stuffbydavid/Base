#pragma once

#include "util/data/vec3.hpp"
#include "util/mathfunc.hpp"


namespace Base
{
    /* 4x4 Matrix */
    template<typename T> struct Mat4x4
    {
        // Matrix elements
        T elem[16];

        // Constructors

        Mat4x4()
        {
            elem[0] = 1.f; elem[4] = 0.f; elem[8] = 0.f; elem[12] = 0.f;
            elem[1] = 0.f; elem[5] = 1.f; elem[9] = 0.f; elem[13] = 0.f;
            elem[2] = 0.f; elem[6] = 0.f; elem[10] = 1.f; elem[14] = 0.f;
            elem[3] = 0.f; elem[7] = 0.f; elem[11] = 0.f; elem[15] = 1.f;
        }

        Mat4x4(T x1, T y1, T z1, T w1,
               T x2, T y2, T z2, T w2,
               T x3, T y3, T z3, T w3,
               T x4, T y4, T z4, T w4)
        {
            elem[0] = x1; elem[4] = y1; elem[8] = z1; elem[12] = w1;
            elem[1] = x2; elem[5] = y2; elem[9] = z2; elem[13] = w2;
            elem[2] = x3; elem[6] = y3; elem[10] = z3; elem[14] = w3;
            elem[3] = x4; elem[7] = y4; elem[11] = z4; elem[15] = w4;
        }

        inline Mat4x4(const Mat4x4& other)
        {
            for (int i = 0; i < 16; i++)
                elem[i] = other.elem[i];
        }

        inline Mat4x4& operator=(const Mat4x4& other)
        {
            for (int i = 0; i < 16; i++)
                elem[i] = other.elem[i];
            return *this;
        }

        // Methods

        /* Builds a translation matrix. */
        static inline Mat4x4 translate(const Vec3<T>& vec)
        {
            return Mat4x4(
                1.f, 0.f, 0.f, vec.x,
                0.f, 1.f, 0.f, vec.y,
                0.f, 0.f, 1.f, vec.z,
                0.f, 0.f, 0.f, 1.f
            );
        }

        /* Builds a rotation matrix around an axis. */
        static inline Mat4x4 rotate(const Vec3<T>& around, T angle)
        {
            /*Vec3 u = around;
            T s = dsin(angle);
            T c = dcos(angle);
            return Mat4x4(
                u.x*u.x+(1.f-u.x*u.x)*c,  u.x*u.y*(1.f-c)-u.z*s,    u.x*u.z*(1.f-c)+u.y*s,    0.f,
                u.x*u.y*(1.f-c)+u.z*s,    u.y*u.y+(1.f-u.y*u.y)*c,  u.y*u.z*(1.f-c)-u.x*s,    0.f,
                u.x*u.z*(1.f-c)-u.y*s,    u.y*u.z*(1.f-c)+u.x*s,    u.z*u.z+(1.f-u.z*u.z)*c,  0.f,
                0.f,                      0.f,                      0.f,                      1.f
            );*/
            // TODO: Work for any angle
            return Mat4x4(
                dcos(angle), -dsin(angle), 0.f, 0.f,
                dsin(angle), dcos(angle), 0.f, 0.f,
                0.f, 0.f, 1.f, 0.f,
                0.f, 0.f, 0.f, 1.f
            );
        }

        /* Builds a scaling matrix. */
        static inline Mat4x4 scale(const Vec3<T>& s)
        {
            return Mat4x4(
                s.x, 0.f, 0.f, 0.f,
                0.f, s.y, 0.f, 0.f,
                0.f, 0.f, s.z, 0.f,
                0.f, 0.f, 0.f, 1.f
            );
        }

        /* Builds an orthographic matrix. */
        static inline Mat4x4 ortho(T left, T right, T bottom, T top, T znear, T zfar)
        {
            return Mat4x4(
                2.f / (right - left), 0.f, 0.f, -(right + left) / (right - left),
                0.f, 2.f / (top - bottom), 0.f, -(top + bottom) / (top - bottom),
                0.f, 0.f, -2.f / (zfar - znear), -(zfar + znear) / (zfar - znear),
                0.f, 0.f, 0.f, 1.f
            );
        }

        /* Builds a perspective matrix. */
        static Mat4x4 perspective(T tFov, T ratio, T znear, T zfar)
        {
            T iFov = 1.f / tFov;
            return Mat4x4(
                iFov / ratio, 0.f, 0.f, 0.f,
                0.f, iFov, 0.f, 0.f,
                0.f, 0.f, (zfar + znear) / (znear - zfar), (2.f * zfar * znear) / (znear - zfar),
                0.f, 0.f, -1.f, 0.f
            );
        }

        /* Builds a view matrix from a x, y and z axis. */
        static inline Mat4x4 view(const Vec3<T>& xaxis, const Vec3<T>& yaxis, const Vec3<T>& zaxis)
        {
            return Mat4x4(
                xaxis.x, xaxis.y, xaxis.z, 0.f,
                yaxis.x, yaxis.y, yaxis.z, 0.f,
                -zaxis.x, -zaxis.y, -zaxis.z, 0.f,
                0.f, 0.f, 0.f, 1.f
            );
        }

        // Binary operators

        Mat4x4 operator * (const Mat4x4& other)
        {
            Mat4x4 product;
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    product.elem[j * 4 + i] = 0.f;

                    for (int k = 0; k < 4; k++)
                        product.elem[j * 4 + i] += elem[k * 4 + i] * other.elem[j * 4 + k];
                }
            }
            return product;
        }

        inline Vec3<T> operator * (const Vec3<T>& other)
        {
            return Vec3<T>(
                elem[0] * other.x + elem[4] * other.y + elem[8] * other.z + elem[12] * 0.f,
                elem[1] * other.x + elem[5] * other.y + elem[9] * other.z + elem[13] * 0.f,
                elem[2] * other.x + elem[6] * other.y + elem[10] * other.z + elem[14] * 0.f
            );
        }
    };

    template<typename T> std::ostream& operator << (std::ostream& cout, const Mat4x4<T>& mat)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
                cout << mat.elem[j * 4 + i] << (j < 3 ? "," : "");
            cout << endl;
        }
        return cout;
    }

    template<typename T> inline void operator *= (Mat4x4<T>& a, const Mat4x4<T>& b)
    {
        a = a * b;
    }

    // Define shorthands
    using Mat4x4i = Mat4x4<int>;
    using Mat4x4f = Mat4x4<float>;
    using Mat4x4d = Mat4x4<double>;
}