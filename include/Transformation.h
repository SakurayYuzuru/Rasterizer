#include <Camera.h>
#include <Global.h>

namespace Transformation{
    Matrix scale(const float& k);
    Matrix translate(const Vector3f& v);
    Matrix rotate(const float& angle, const Vector3f& v);

    Matrix lookat(const Vector3f& eye, const Vector3f& target, const Vector3f& up);
    Matrix get_view_matrix(const Vector3f& eye_pos);
    Matrix get_model_matrix(const float& angle);
    Matrix get_projection_matrix(const float& eye_fov, const float& aspect_ratio, const float& zNear, const float& zFar);
};