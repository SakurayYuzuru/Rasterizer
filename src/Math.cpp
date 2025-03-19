#include <Math.h>

float Math::radians(float degrees) {
    return degrees * PI / 180;
}
Math::Vector3f Math::radians(Math::Vector3f &angle){
    return Math::Vector3f(angle.x / PI * 180.0f, angle.y / PI * 180.0f, angle.z / PI * 180.0f);
}

Math::Vector2f::Vector2f() : x(0), y(0) {}
Math::Vector2f::Vector2f(float x, float y) : x(x), y(y) {}
Math::Vector2f::Vector2f(const Math::Vector2f& v) : x(v.x), y(v.y) {}
Math::Vector2f::~Vector2f() {}

Math::Vector2f Math::Vector2f::Identity() {
    return Math::Vector2f(1, 1);
}

Math::Vector2f Math::Vector2f::operator+(const Math::Vector2f& v) const {
    return Vector2f(this->x + v.x, this->y + v.y);
}
Math::Vector2f Math::Vector2f::operator-(const Math::Vector2f& v) const {
    return Vector2f(this->x - v.x, this->y - v.y);
}
Math::Vector2f Math::Vector2f::operator*(const float &k) const {
    return Math::Vector2f(this->x * k, this->y * k);
}
Math::Vector2f Math::Vector2f::operator/(const float &k) const {
    return Math::Vector2f(this->x / k, this->y / k);
}
Math::Vector2f& Math::Vector2f::operator=(const Math::Vector2f& v) {
    this->x = v.x;
    this->y = v.y;
    return *this;
}

float Math::Vector2f::dot(const Math::Vector2f& v) const {
    return this->x * v.x + this->y * v.y;
}
Math::Vector2f Math::Vector2f::cwise(const Math::Vector2f& v) const {
    return Math::Vector2f(this->x * v.x, this->y * v.y);
}
float Math::Vector2f::norm() const {
    return std::sqrt(this->x * this->x + this->y * this->y);
}
Math::Vector2f Math::Vector2f::normalized() const {
    return *this / this->norm();
}

std::ostream& operator<<(std::ostream& os, const Math::Vector2f& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

float& Math::Vector2f::operator[](int index) {
    if (index < 0 || index > 1) throw std::out_of_range("Index out of range");
    return *(&x + index);
}
const float& Math::Vector2f::operator[](int index) const {
    if (index < 0 || index > 1) throw std::out_of_range("Index out of range");
    return *(&x + index);
}

Math::Vector3f::Vector3f() : x(0), y(0), z(0) {}
Math::Vector3f::Vector3f(float x, float y, float z) : x(x), y(y), z(z) {}
Math::Vector3f::Vector3f(const Math::Vector3f& v) : x(v.x), y(v.y), z(v.z) {}
Math::Vector3f::~Vector3f() {}

Math::Vector3f Math::Vector3f::Identity() {
    return Math::Vector3f(1, 1, 1);
}

Math::Vector3f Math::Vector3f::operator+(const Math::Vector3f& v) const {
    return Vector3f(this->x + v.x, this->y + v.y, this->z + v.z);
}
Math::Vector3f Math::Vector3f::operator-(const Math::Vector3f& v) const {
    return Vector3f(this->x - v.x, this->y - v.y, this->z - v.z);
}
Math::Vector3f Math::Vector3f::operator*(const float &k) const {
    return Math::Vector3f(this->x * k, this->y * k, this->z * k);
}
Math::Vector3f Math::Vector3f::operator*(const Math::Matrix &m) const{
    Math::Vector3f res;
    for(int i = 0; i < 3; ++ i){
        for(int j = 0; j < 3; ++ j){
            res[i] += (*this)[i] * m[i][j];
        }
    }

    return res;
}
Math::Vector3f Math::Vector3f::operator/(const float &k) const {
    return Math::Vector3f(this->x / k, this->y / k, this->z / k);
}
Math::Vector3f& Math::Vector3f::operator=(const Math::Vector3f& v) {
    if (this != &v) {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
    }
    return *this;
}

float Math::Vector3f::dot(const Math::Vector3f& v) const {
    return this->x * v.x + this->y * v.y + this->z * v.z;
}
Math::Vector3f Math::Vector3f::cross(const Math::Vector3f& v) const {
    return Vector3f(this->y * v.z - this->z * v.y, this->z * v.x - this->x * v.z, this->x * v.y - this->y * v.x);
}
Math::Vector3f Math::Vector3f::cwise(const Math::Vector3f& v) const {
    return Vector3f(this->x * v.x, this->y * v.y, this->z * v.z);
}
float Math::Vector3f::norm() const {
    return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}
Math::Vector3f Math::Vector3f::normalized() const {
    return *this / this->norm();
}
Math::Vector4f Math::Vector3f::to_Vector4f(const float &w) const {
    return Vector4f(this->x, this->y, this->z, w);
}

Math::Vector3f operator*(const float &k, const Math::Vector3f& v) {
    return v * k;
}
std::ostream& operator<<(std::ostream& os, const Math::Vector3f& v){
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

float& Math::Vector3f::operator[](int index) {
    if (index < 0 || index > 2) throw std::out_of_range("Index out of range");
    return *(&x + index);
}
const float& Math::Vector3f::operator[](int index) const {
    if (index < 0 || index > 2) throw std::out_of_range("Index out of range");
    return *(&x + index);
}

Math::Vector4f::Vector4f() : x(0), y(0), z(0), w(0) {}
Math::Vector4f::Vector4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
Math::Vector4f::Vector4f(const Math::Vector4f& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
Math::Vector4f::~Vector4f() {}

Math::Vector4f Math::Vector4f::Identity() {
    return Vector4f(1, 1, 1, 1);
}

Math::Vector4f Math::Vector4f::operator+(const Math::Vector4f& v) const {
    return Math::Vector4f(this->x + v.x, this->y + v.y, this->z + v.z, this->w + v.w);
}
Math::Vector4f Math::Vector4f::operator-(const Math::Vector4f& v) const {
    return Math::Vector4f(this->x - v.x, this->y - v.y, this->z - v.z, this->w - v.w);
}
Math::Vector4f Math::Vector4f::operator*(const float &k) const {
    return Vector4f(this->x * k, this->y * k, this->z * k, this->w * k);
}
Math::Vector4f Math::Vector4f::operator*(const Math::Matrix &m) const{
    Math::Vector4f res;
    for(int i = 0; i < 4; ++ i){
        for(int j = 0; j < 4; ++ j){
            res[i] += (*this)[i] * m[i][j];
        }
    }

    return res;
}
Math::Vector4f Math::Vector4f::operator/(const float &k) const {
    return Math::Vector4f(this->x / k, this->y / k, this->z / k, this->w / k);
}
Math::Vector4f& Math::Vector4f::operator=(const Math::Vector4f& v) {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    this->w = v.w;
    return *this;
}

float Math::Vector4f::dot(const Math::Vector4f& v) const {
    return this->x * v.x + this->y * v.y + this->z * v.z + this->w * v.w;
}
Math::Vector4f Math::Vector4f::cwise(const Math::Vector4f& v) const {
    return Math::Vector4f(this->x * v.x, this->y * v.y, this->z * v.z, this->w * v.w);
}
float Math::Vector4f::norm() const {
    return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
}
Math::Vector4f Math::Vector4f::normalized() const {
    return *this / this->norm();
}
Math::Vector3f Math::Vector4f::to_Vector3f() const {
    return Math::Vector3f(this->x / this->w, this->y / this->w, this->z / this->w);
}

float& Math::Vector4f::operator[](int index) {
    if (index < 0 || index > 3) throw std::out_of_range("Index out of range");
    return *(&x + index);
}
const float& Math::Vector4f::operator[](int index) const {
    if (index < 0 || index > 3) throw std::out_of_range("Index out of range");
    return *(&x + index);
}

std::ostream& operator<<(std::ostream& os, const Math::Vector4f& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
    return os;
}

Math::Matrix::Matrix() : rows(0), cols(0), data({}) {}
Math::Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) {
    this->data = std::vector<std::vector<float>>(rows, std::vector<float>(cols, 0));
}
Math::Matrix::Matrix(const Math::Matrix& m) : rows(m.rows), cols(m.cols), data(m.data) {}
Math::Matrix::~Matrix() {}

Math::Matrix Math::Matrix::Identity(){
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

Math::Matrix Math::Matrix::operator+(const Math::Matrix& m) const {
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
Math::Matrix Math::Matrix::operator-(const Math::Matrix& m) const {
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
Math::Matrix Math::Matrix::operator*(const Math::Matrix& m) const {
    if (this->cols != m.rows) {
        throw std::invalid_argument("Matrix dimensions do not match");
    }
    Math::Matrix result(this->rows, m.cols);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            for (int k = 0; k < this->cols; k++) {
                result.data[i][j] += this->data[i][k] * m.data[k][j];
            }
        }
    }
    return result;
}
Math::Matrix Math::Matrix::operator*(const float &k) const {
    Math::Matrix result(this->rows, this->cols);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            result.data[i][j] = this->data[i][j] * k;
        }
    }
    return result;
}
Math::Vector3f Math::Matrix::operator*(const Vector3f& v) const{
    Vector3f res;
    for(int i = 0; i < 3; ++ i){
        for(int j = 0; j < 3; ++ j){
            res[i] += v[i] * (*this)[i][j];
        }
    }

    return res;
}
Math::Vector4f Math::Matrix::operator*(const Vector4f &v) const{
    Vector4f res;
    for(int i = 0; i < 4; ++ i){
        for(int j = 0; j < 4; ++ j){
            res[i] += v[i] * (*this)[i][j];
        }
    }

    return res;
}
Math::Matrix Math::Matrix::operator/(const float &k) const {
    Matrix result(this->rows, this->cols);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            result.data[i][j] = this->data[i][j] / k;
        }
    }
    return result;
}
Math::Matrix& Math::Matrix::operator=(const Math::Matrix& m) {
    this->rows = m.rows;
    this->cols = m.cols;
    this->data = m.data;
    return *this;
}

float Math::Matrix::cofactor(int row, int col) const {
    if (this->rows != this->cols) {
        throw std::invalid_argument("Matrix is not square");
    }
    Math::Matrix minor(this->rows - 1, this->cols - 1);
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
Math::Matrix Math::Matrix::transpose() const{
    Math::Matrix result(this->cols, this->rows);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            result.data[j][i] = this->data[i][j];
        }
    }
    return result;
}
Math::Matrix Math::Matrix::inverse() const{
    if (this->rows != this->cols) {
        throw std::invalid_argument("Matrix is not square");
    }
    float det = this->determinant();
    if (det == 0) {
        throw std::invalid_argument("Matrix is singular");
    }
    Math::Matrix result(this->rows, this->cols);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            result.data[i][j] = this->cofactor(i, j) / det;
        }
    }
    return result;
}
float Math::Matrix::determinant() const{
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

int Math::Matrix::col() const{
    return this->cols;
}
int Math::Matrix::row() const{
    return this->rows;
}

std::ostream& operator<<(std::ostream& os, const Math::Matrix& m) {
    for (int i = 0; i < m.row(); i++) {
        for (int j = 0; j < m.col(); j++) {
            os << m[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}

std::vector<float>& Math::Matrix::operator[](int index) {
    if (index < 0 || index >= rows) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}
const std::vector<float>& Math::Matrix::operator[](int index) const {
    if (index < 0 || index >= rows) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

Math::Vector3f Math::interpolate(float alpha, float beta, float gamma, const Math::Vector3f& vec1, const Math::Vector3f& vec2, const Math::Vector3f& vec3, float weight){
    return (vec1 * alpha + vec2 * beta + vec3 * gamma) / weight;
}
Math::Vector2f Math::interpolate(float alpha, float beta, float gamma, const Math::Vector2f& vec1, const Math::Vector2f& vec2, const Math::Vector2f& vec3, float weight){
    auto u = (alpha * vec1.x + beta * vec2.x + gamma * vec3.x);
    auto v = (alpha * vec1.y + beta * vec2.y + gamma * vec3.x);
    
    u /= weight;
    v /= weight;

    return Math::Vector2f(u, v);
}