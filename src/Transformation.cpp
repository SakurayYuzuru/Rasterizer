#include <Transformation.h>

Matrix Transformation::scale(const float& k){
    Matrix scale = Matrix::Identity();

    for (int i = 0; i < 4; ++ i) {
        for(int j = 0; j < 4; ++ j) {
            if(i == j){
                scale[i][j] = k;
            }else {
                scale[i][j] = 0;
            }
        }
    }

    return scale;
}

Matrix Transformation::translate(const Vector3f& v){
    Matrix translate = Matrix::Identity();

    for (int i = 0; i < 4; ++ i) {
        for(int j = 0; j < 4; ++ j) {
            if(i == j){
                translate[i][j] = 1;
            }else if(j == 3){
                translate[i][j] = v[i];
            }else {
                translate[i][j] = 0;
            }
        }
    }

    return translate;
}

Matrix Transformation::rotate(const float& angle, const Vector3f& v){
    Matrix rotation = Matrix::Identity();
    float theta = angle * PI / 180.0f;
    float sin = std::sin(theta / 2), cos = std::cos(theta / 2);
    Vector3f axis = v.normalized();
    Matrix quaternion(4, 4);

    quaternion[0][0] = axis.x * axis.x * (1 - cos) + cos;
    quaternion[0][1] = axis.x * axis.y * (1 - cos) + axis.z * sin;
    quaternion[0][2] = axis.x * axis.z * (1 - cos) - axis.y * sin;
    quaternion[0][3] = 0.0f;

    quaternion[1][0] = axis.x * axis.y * (1 - cos) - axis.z * sin;
    quaternion[1][1] = axis.y * axis.y * (1 - cos) + cos;
    quaternion[1][2] = axis.y * axis.z * (1 - cos) + axis.x * sin;
    quaternion[1][3] = 0.0f;

    quaternion[2][0] = axis.x * axis.z * (1 - cos) + axis.y * sin;
    quaternion[2][1] = axis.y * axis.z * (1 - cos) - axis.x * sin;
    quaternion[2][2] = axis.z * axis.z * (1 - cos) + cos;
    quaternion[2][3] = 0.0f;

    quaternion[3][0] = 0.0f;
    quaternion[3][1] = 0.0f;
    quaternion[3][2] = 0.0f;
    quaternion[3][3] = 1.0f;

    rotation = quaternion * rotation;

    return rotation;
}

Matrix Transformation::lookat(const Vector3f& eye, const Vector3f& target, const Vector3f& up){
    Vector3f f = (target - eye).normalized();
    Vector3f r = f.cross(up).normalized();
    Vector3f u = r.cross(f).normalized();

    Matrix lookat = Matrix::Identity();

    for (int i = 0; i < 3; ++ i) {
        lookat[0][i] = r[i];
        lookat[1][i] = u[i];
        lookat[2][i] = -f[i];
    }

    lookat[0][3] = -r.dot(eye);
    lookat[1][3] = -u.dot(eye);
    lookat[2][3] = f.dot(eye);

    return lookat;
}

Matrix Transformation::get_view_matrix(const Vector3f& eye_pos){
    Matrix view = Matrix::Identity();

    view[0][3] = -eye_pos.x;
    view[1][3] = -eye_pos.y;
    view[2][3] = -eye_pos.z;

    return view;
}

Matrix Transformation::get_model_matrix(const float& angle){
    Matrix model = Matrix::Identity();
    float theta = angle * PI / 180.0f;
    Matrix rotation = rotate(theta, Vector3f(0, 0, 1));

    model = rotation * model;

    return model;
}

Matrix Transformation::get_projection_matrix(const float& eye_fov, const float& aspect_ratio, const float& zNear, const float& zFar){
    Matrix projection = Matrix::Identity();

    float halfTheta = eye_fov * PI / 180.0f / 2.0f;
    float t = -std::tan(halfTheta) * zNear;
    float b = -t;
    float l = t * aspect_ratio;
    float r = -l;

    Matrix ortho = Matrix::Identity();
    ortho[0][0] = 2 / (r - l);
    ortho[1][1] = 2 / (t - b);
    ortho[2][2] = -2 / (zFar - zNear);

    Matrix translate = Matrix::Identity();
    translate[0][3] = -(r + l) / (r - l);
    translate[1][3] = -(t + b) / (t - b);
    translate[2][3] = -(zFar + zNear) / (zFar - zNear);

    Matrix persp2ortho = Matrix::Identity();
    persp2ortho[0][0] = zNear;
    persp2ortho[1][1] = zNear;
    persp2ortho[2][2] = zNear + zFar;
    persp2ortho[2][3] = -zNear * zFar;
    persp2ortho[3][2] = 1;
    persp2ortho[3][3] = 0;

    projection = projection * ortho * translate * persp2ortho;

    return projection;
}