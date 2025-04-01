#include <Transformation.h>

Math::Matrix Transformation::scale(const float& k){
    Math::Matrix scale = Math::Matrix::Identity();

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

Math::Matrix Transformation::translate(const Math::Vector3f& v){
    Math::Matrix translate = Math::Matrix::Identity();

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

Math::Matrix Transformation::rotate(const float& angle, const Math::Vector3f& v){
    Math::Matrix rotation = Math::Matrix::Identity();
    float theta = angle * PI / 180.0f;
    float sin = std::sin(theta), cos = std::cos(theta);
    Math::Vector3f axis = v.normalized();
    Math::Matrix quaternion(4, 4);

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

Math::Matrix Transformation::lookat(const Math::Vector3f& eye, const Math::Vector3f& target, const Math::Vector3f& up){
    Math::Vector3f f = (target - eye).normalized();
    Math::Vector3f r = f.cross(up).normalized();
    Math::Vector3f u = r.cross(f).normalized();

    Math::Matrix lookat = Math::Matrix::Identity();

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

Math::Matrix Transformation::get_view_matrix(const Math::Vector3f& eye_pos){
    Math::Matrix view = Math::Matrix::Identity();

    view[0][3] = -eye_pos.x;
    view[1][3] = -eye_pos.y;
    view[2][3] = -eye_pos.z;

    return view;
}

Math::Matrix Transformation::get_model_matrix(const float& angle){
    Math::Matrix model = Math::Matrix::Identity();
    float theta = angle * PI / 180.0f;
    Math::Matrix rotation = Transformation::rotate(theta, Math::Vector3f(0.0f, 1.0f, 0.0f));

    model = rotation * model;

    return model;
}

Math::Matrix Transformation::get_projection_matrix(const float& eye_fov, const float& aspect_ratio, const float& zNear, const float& zFar){
    Math::Matrix projection = Math::Matrix::Identity();

    float halfTheta = eye_fov * PI / 180.0f / 2.0f;
    float t = -std::tan(halfTheta) * zNear;
    float b = -t;
    float l = t * aspect_ratio;
    float r = -l;

    Math::Matrix ortho = Math::Matrix::Identity();
    ortho[0][0] = 2 / (l - r);
    ortho[1][1] = 2 / (t - b);
    ortho[2][2] = -2 / (zFar - zNear);

    Math::Matrix translate = Math::Matrix::Identity();
    translate[0][3] = -(r + l) / (r - l);
    translate[1][3] = -(t + b) / (t - b);
    translate[2][3] = -(zFar + zNear) / (zFar - zNear);

    Math::Matrix persp2ortho = Math::Matrix::Identity();
    persp2ortho[0][0] = zNear;
    persp2ortho[1][1] = zNear;
    persp2ortho[2][2] = zNear + zFar;
    persp2ortho[2][3] = -zNear * zFar;
    persp2ortho[3][2] = 1;
    persp2ortho[3][3] = 0;

    projection = projection * ortho * translate * persp2ortho;

    return projection;
}