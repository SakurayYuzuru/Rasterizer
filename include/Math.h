#ifndef MATH_H
#define MATH_H

#pragma once

#include <iostream>
#include <vector>
#include <Global.h>

class Vector4f;
class Matrix;

class Vector2f {
    friend std::ostream& operator<<(std::ostream& os, const Vector2f& v);

public:
    Vector2f();
    Vector2f(float x, float y);
    Vector2f(const Vector2f& v);
    ~Vector2f();

    static Vector2f Identity();

    Vector2f operator+(const Vector2f& v) const;
    Vector2f operator-(const Vector2f& v) const;
    Vector2f operator*(const float &k) const;
    Vector2f operator/(const float &k) const;
    Vector2f& operator=(const Vector2f& v);

    float dot(const Vector2f& v) const;
    Vector2f cwise(const Vector2f& v) const;
    float norm() const;
    Vector2f normalized() const;

    float& operator[](int index);
    const float& operator[](int index) const;

    float x, y;
};

std::ostream& operator<<(std::ostream& os, const Vector2f& v);

class Vector3f {
    friend Vector3f operator*(const float &k, const Vector3f& v);
    friend std::ostream& operator<<(std::ostream& os, const Vector3f& v);

public:
    Vector3f();
    Vector3f(float x, float y, float z);
    Vector3f(const Vector3f& v);
    ~Vector3f();

    static Vector3f Identity();

    Vector3f operator+(const Vector3f& v) const;
    Vector3f operator-(const Vector3f& v) const;
    Vector3f operator*(const float &k) const;
    Vector3f operator*(const Matrix &m) const;
    Vector3f operator/(const float &k) const;
    Vector3f& operator=(const Vector3f& v);

    float dot(const Vector3f& v) const;
    Vector3f cross(const Vector3f& v) const;
    Vector3f cwise(const Vector3f& v) const;
    float norm() const;
    Vector3f normalized() const;
    Vector4f to_Vector4f(const float &w) const;

    float& operator[](int index);
    const float& operator[](int index) const;

    float x, y, z;
};

Vector3f operator*(const float &k, const Vector3f& v);
std::ostream& operator<<(std::ostream& os, const Vector3f& v);

class Vector4f{
    friend std::ostream& operator<<(std::ostream& os, const Vector4f& v);

public:
    Vector4f();
    Vector4f(float x, float y, float z, float w);
    Vector4f(const Vector4f& v);
    ~Vector4f();

    static Vector4f Identity();

    Vector4f operator+(const Vector4f& v) const;
    Vector4f operator-(const Vector4f& v) const;
    Vector4f operator*(const float &k) const;
    Vector4f operator*(const Matrix &m) const;
    Vector4f operator/(const float &k) const;
    Vector4f& operator=(const Vector4f& v);

    float dot(const Vector4f& v) const;
    Vector4f cross(const Vector4f& v) const;
    Vector4f cwise(const Vector4f& v) const;
    float norm() const;
    Vector4f normalized() const;
    Vector3f to_Vector3f() const;

    float& operator[](int index);
    const float& operator[](int index) const;

    float x, y, z, w;
};

std::ostream& operator<<(std::ostream& os, const Vector4f& v);

class Matrix {
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);

public:
    Matrix();
    Matrix(int rows, int cols);
    Matrix(const Matrix& m);
    ~Matrix();

    static Matrix Identity();

    Matrix operator+(const Matrix& m) const;
    Matrix operator-(const Matrix& m) const;
    Matrix operator*(const Matrix& m) const;
    Matrix operator*(const float &k) const;
    Vector4f operator*(const Vector4f &v) const;
    Matrix operator/(const float &k) const;
    Matrix& operator=(const Matrix& m);

    float cofactor(int row, int col) const;
    Matrix transpose() const;
    Matrix inverse() const;
    float determinant() const;

    std::vector<float>& operator[](int index);
    const std::vector<float>& operator[](int index) const;

private:
    int rows, cols;
    std::vector<std::vector<float>> data;
};

std::ostream& operator<<(std::ostream& os, const Matrix& m);

float radians(float degrees);
Vector3f radians(Vector3f &angle);

#endif