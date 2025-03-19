#ifndef SHADER_H
#define SHADER_H

#pragma once

#include <Vertex.hpp>
#include <Color.h>

namespace Shader{
    Color normal_fragment_shader(const Vertex& payload, const Math::Vector3f& eye_pos);
    Color texture_fragment_shader(const Vertex& payload, const Math::Vector3f& eye_pos);
    Color phong_fragment_shader(const Vertex& payload, const Math::Vector3f& eye_pos);
    Color displacement_fragment_shader(const Vertex& payload, const Math::Vector3f& eye_pos);
    Color bump_fragment_shader(const Vertex& payload, const Math::Vector3f& eye_pos);
};

#endif