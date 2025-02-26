#include <Math.h>

float radians(float degrees) {
    return degrees * PI / 180;
}
Vector3f radians(Vector3f &angle){
    return Vector3f(angle.x / PI * 180.0f, angle.y / PI * 180.0f, angle.z / PI * 180.0f);
}

Vector2f::Vector2f() : x(0), y(0) {}
Vector2f::Vector2f(float x, float y) : x(x), y(y) {}
Vector2f::Vector2f(const Vector2f& v) : x(v.x), y(v.y) {}
Vector2f::~Vector2f() {}

Vector2f Vector2f::Identity() {
    return Vector2f(1, 1);
}

Vector2f Vector2f::operator+(const Vector2f& v) const {
    return Vector2f(this->x + v.x, this->y + v.y);
}
Vector2f Vector2f::operator-(const Vector2f& v) const {
    return Vector2f(this->x - v.x, this->y - v.y);
}
Vector2f Vector2f::operator*(const float &k) const {
    return Vector2f(this->x * k, this->y * k);
}
Vector2f Vector2f::operator/(const float &k) const {
    return Vector2f(this->x / k, this->y / k);
}
Vector2f& Vector2f::operator=(const Vector2f& v) {
    this->x = v.x;
    this->y = v.y;
    return *this;
}

float Vector2f::dot(const Vector2f& v) const {
    return this->x * v.x + this->y * v.y;
}
Vector2f Vector2f::cwise(const Vector2f& v) const {
    return Vector2f(this->x * v.x, this->y * v.y);
}
float Vector2f::norm() const {
    return std::sqrt(this->x * this->x + this->y * this->y);
}
Vector2f Vector2f::normalized() const {
    return *this / this->norm();
}

std::ostream& operator<<(std::ostream& os, const Vector2f& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

float& Vector2f::operator[](int index) {
    if (index < 0 || index > 1) throw std::out_of_range("Index out of range");
    return *(&x + index);
}
const float& Vector2f::operator[](int index) const {
    if (index < 0 || index > 1) throw std::out_of_range("Index out of range");
    return *(&x + index);
}

Vector3f::Vector3f() : x(0), y(0), z(0) {}
Vector3f::Vector3f(float x, float y, float z) : x(x), y(y), z(z) {}
Vector3f::Vector3f(const Vector3f& v) : x(v.x), y(v.y), z(v.z) {}
Vector3f::~Vector3f() {}

Vector3f Vector3f::Identity() {
    return Vector3f(1, 1, 1);
}

Vector3f Vector3f::operator+(const Vector3f& v) const {
    return Vector3f(this->x + v.x, this->y + v.y, this->z + v.z);
}
Vector3f Vector3f::operator-(const Vector3f& v) const {
    return Vector3f(this->x - v.x, this->y - v.y, this->z - v.z);
}
Vector3f Vector3f::operator*(const float &k) const {
    return Vector3f(this->x * k, this->y * k, this->z * k);
}
Vector3f Vector3f::operator*(const Matrix &m) const{
    Vector3f res;
    for(int i = 0; i < 3; ++ i){
        for(int j = 0; j < 3; ++ j){
            res[i] += (*this)[i] * m[i][j];
        }
    }

    return res;
}
Vector3f Vector3f::operator/(const float &k) const {
    return Vector3f(this->x / k, this->y / k, this->z / k);
}
Vector3f& Vector3f::operator=(const Vector3f& v) {
    if (this != &v) {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
    }
    return *this;
}

float Vector3f::dot(const Vector3f& v) const {
    return this->x * v.x + this->y * v.y + this->z * v.z;
}
Vector3f Vector3f::cross(const Vector3f& v) const {
    return Vector3f(this->y * v.z - this->z * v.y, this->z * v.x - this->x * v.z, this->x * v.y - this->y * v.x);
}
Vector3f Vector3f::cwise(const Vector3f& v) const {
    return Vector3f(this->x * v.x, this->y * v.y, this->z * v.z);
}
float Vector3f::norm() const {
    return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}
Vector3f Vector3f::normalized() const {
    return *this / this->norm();
}
Vector4f Vector3f::to_Vector4f(const float &w) const {
    return Vector4f(this->x, this->y, this->z, w);
}

Vector3f operator*(const float &k, const Vector3f& v) {
    return v * k;
}
std::ostream& operator<<(std::ostream& os, const Vector3f& v){
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

float& Vector3f::operator[](int index) {
    if (index < 0 || index > 2) throw std::out_of_range("Index out of range");
    return *(&x + index);
}
const float& Vector3f::operator[](int index) const {
    if (index < 0 || index > 2) throw std::out_of_range("Index out of range");
    return *(&x + index);
}

Vector4f::Vector4f() : x(0), y(0), z(0), w(0) {}
Vector4f::Vector4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
Vector4f::Vector4f(const Vector4f& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
Vector4f::~Vector4f() {}

Vector4f Vector4f::Identity() {
    return Vector4f(1, 1, 1, 1);
}

Vector4f Vector4f::operator+(const Vector4f& v) const {
    return Vector4f(this->x + v.x, this->y + v.y, this->z + v.z, this->w + v.w);
}
Vector4f Vector4f::operator-(const Vector4f& v) const {
    return Vector4f(this->x - v.x, this->y - v.y, this->z - v.z, this->w - v.w);
}
Vector4f Vector4f::operator*(const float &k) const {
    return Vector4f(this->x * k, this->y * k, this->z * k, this->w * k);
}
Vector4f Vector4f::operator*(const Matrix &m) const{
    Vector4f res;
    for(int i = 0; i < 4; ++ i){
        for(int j = 0; j < 4; ++ j){
            res[i] += (*this)[i] * m[i][j];
        }
    }

    return res;
}
Vector4f Vector4f::operator/(const float &k) const {
    return Vector4f(this->x / k, this->y / k, this->z / k, this->w / k);
}
Vector4f& Vector4f::operator=(const Vector4f& v) {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    this->w = v.w;
    return *this;
}

float Vector4f::dot(const Vector4f& v) const {
    return this->x * v.x + this->y * v.y + this->z * v.z + this->w * v.w;
}
Vector4f Vector4f::cwise(const Vector4f& v) const {
    return Vector4f(this->x * v.x, this->y * v.y, this->z * v.z, this->w * v.w);
}
float Vector4f::norm() const {
    return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
}
Vector4f Vector4f::normalized() const {
    return *this / this->norm();
}
Vector3f Vector4f::to_Vector3f() const {
    return Vector3f(this->x / this->w, this->y / this->w, this->z / this->w);
}

float& Vector4f::operator[](int index) {
    if (index < 0 || index > 3) throw std::out_of_range("Index out of range");
    return *(&x + index);
}
const float& Vector4f::operator[](int index) const {
    if (index < 0 || index > 3) throw std::out_of_range("Index out of range");
    return *(&x + index);
}

std::ostream& operator<<(std::ostream& os, const Vector4f& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
    return os;
}

Matrix::Matrix() : rows(0), cols(0), data({}) {}
Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) {
    this->data = std::vector<std::vector<float>>(rows, std::vector<float>(cols, 0));
}
Matrix::Matrix(const Matrix& m) : rows(m.rows), cols(m.cols), data(m.data) {}
Matrix::~Matrix() {}

Matrix Matrix::Identity(){
    Matrix res(4, 4);
    for (int i = 0; i < 4; ++ i) {
        for(int j = 0; j < 4; ++ j) {
            if(i == j){
                res[i][j] = 1;
            }else {
                res[i][j] = 0;
            }
        }
    }

    return res;
}

Matrix Matrix::operator+(const Matrix& m) const {
    if (this->rows != m.rows || this->cols != m.cols) {
        throw std::invalid_argument("Matrix dimensions do not match");
    }
    Matrix result(this->rows, this->cols);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            result.data[i][j] = this->data[i][j] + m.data[i][j];
        }
    }
    return result;
}
Matrix Matrix::operator-(const Matrix& m) const {
    if (this->rows != m.rows || this->cols != m.cols) {
        throw std::invalid_argument("Matrix dimensions do not match");
    }
    Matrix result(this->rows, this->cols);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            result.data[i][j] = this->data[i][j] - m.data[i][j];
        }
    }
    return result;
}
Matrix Matrix::operator*(const Matrix& m) const {
    if (this->cols != m.rows) {
        throw std::invalid_argument("Matrix dimensions do not match");
    }
    Matrix result(this->rows, m.cols);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            for (int k = 0; k < this->cols; k++) {
                result.data[i][j] += this->data[i][k] * m.data[k][j];
            }
        }
    }
    return result;
}
Matrix Matrix::operator*(const float &k) const {
    Matrix result(this->rows, this->cols);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            result.data[i][j] = this->data[i][j] * k;
        }
    }
    return result;
}
Vector4f Matrix::operator*(const Vector4f &v) const{
    Vector4f res;
    for(int i = 0; i < 4; ++ i){
        for(int j = 0; j < 4; ++ j){
            res[i] += v[i] * (*this)[i][j];
        }
    }

    return res;
}
Matrix Matrix::operator/(const float &k) const {
    Matrix result(this->rows, this->cols);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            result.data[i][j] = this->data[i][j] / k;
        }
    }
    return result;
}
Matrix& Matrix::operator=(const Matrix& m) {
    this->rows = m.rows;
    this->cols = m.cols;
    this->data = m.data;
    return *this;
}

float Matrix::cofactor(int row, int col) const {
    if (this->rows != this->cols) {
        throw std::invalid_argument("Matrix is not square");
    }
    Matrix minor(this->rows - 1, this->cols - 1);
    for (int i = 0, minor_i = 0; i < this->rows; ++i) {
        if (i == row) continue;
        for (int j = 0, minor_j = 0; j < this->cols; ++j) {
            if (j == col) continue;
            minor.data[minor_i][minor_j] = this->data[i][j];
            ++minor_j;
        }
        ++minor_i;
    }
    return minor.determinant() * ((row + col) % 2 == 0 ? 1 : -1);
}
Matrix Matrix::transpose() const{
    Matrix result(this->cols, this->rows);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            result.data[j][i] = this->data[i][j];
        }
    }
    return result;
}
Matrix Matrix::inverse() const{
    if (this->rows != this->cols) {
        throw std::invalid_argument("Matrix is not square");
    }
    float det = this->determinant();
    if (det == 0) {
        throw std::invalid_argument("Matrix is singular");
    }
    Matrix result(this->rows, this->cols);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            result.data[i][j] = this->cofactor(i, j) / det;
        }
    }
    return result;
}
float Matrix::determinant() const{
    if (this->rows != this->cols) {
        throw std::invalid_argument("Matrix is not square");
    }
    if (this->rows == 1) {
        return this->data[0][0];
    }
    float det = 0;
    for (int i = 0; i < this->rows; i++) {
        det += this->data[0][i] * this->cofactor(0, i);
    }
    return det;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            os << m.data[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}

std::vector<float>& Matrix::operator[](int index) {
    if (index < 0 || index >= rows) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}
const std::vector<float>& Matrix::operator[](int index) const {
    if (index < 0 || index >= rows) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}