#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#pragma once

#include <Camera.h>
#include <Global.h>

namespace Transformation{
    Math::Matrix scale(const float& k);
    Math::Matrix translate(const Math::Vector3f& v);
    Math::Matrix rotate(const float& angle, const Math::Vector3f& v);

    Math::Matrix lookat(const Math::Vector3f& eye, const Math::Vector3f& target, const Math::Vector3f& up);
    Math::Matrix get_view_matrix(const Math::Vector3f& eye_pos);
    Math::Matrix get_model_matrix(const float& angle);
    Math::Matrix get_projection_matrix(const float& eye_fov, const float& aspect_ratio, const float& zNear, const float& zFar);
};

#endif