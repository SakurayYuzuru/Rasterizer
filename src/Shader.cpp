#include <Shader.h>
#include <Light.hpp>

Color Shader::normal_fragment_shader(const Vertex& payload, const Math::Vector3f& eye_pos){
    Color return_color = (payload.normal.normalized() + Math::Vector3f(1.0f, 1.0f, 1.0f)) / 2.0f;

    return return_color;
}

Color Shader::texture_fragment_shader(const Vertex& payload, const Math::Vector3f& eye_pos){
    Color return_color;
    if(payload.texture){
        return_color = payload.texture->GetColor(payload.uv);
    }

    Color texture_color = return_color;

    Math::Vector3f ka(0.005f, 0.005f, 0.005f);
    Math::Vector3f kd = texture_color.GetRGB();
    Math::Vector3f ks(0.7937f, 0.7937f, 0.7937f);

    auto l1 = Light{{20, 20, 20}, {500, 500, 500}};
    auto l2 = Light{{-20, 20, 0}, {500, 500, 500}};

    std::vector<Light> lights = {l1, l2};
    Math::Vector3f amb_light_intensity{10, 10, 10};

    float p = 150;

    Math::Vector3f point = payload.v;
    Math::Vector3f normal = payload.normal;

    Math::Vector3f ambient;
    Math::Vector3f diffuse;
    Math::Vector3f specular;

    ambient = ka.cwise(amb_light_intensity);
    Color result_color;

    for(auto& light : lights){
        Math::Vector3f l = light.pos - point;
        float r_square = l.norm();
        l = l.normalized();

        diffuse = diffuse + kd.cwise(light.intensity / (r_square)) * std::max(0.0f, normal.dot(l));

        Math::Vector3f v = (eye_pos - point).normalized();
        Math::Vector3f h = (v + l).normalized();

        specular = specular + ks.cwise(light.intensity / (r_square)) * std::pow(std::max(0.0f, normal.dot(h)), p);
    }
    result_color = ambient + diffuse + specular;

    return result_color;
}

Color Shader::phong_fragment_shader(const Vertex& payload, const Math::Vector3f& eye_pos){
    Math::Vector3f ka(0.005f, 0.005f, 0.005f);
    Math::Vector3f kd = payload.color.GetRGB();
    Math::Vector3f ks(0.7937f, 0.7937f, 0.7937f);

    auto l1 = Light{{20, 20, 20}, {500, 500, 500}};
    auto l2 = Light{{-20, 20, 0}, {500, 500, 500}};

    std::vector<Light> lights = {l1, l2};
    Math::Vector3f amb_light_intensity{10, 10, 10};

    float p = 150;

    Color color = payload.color;
    Math::Vector3f point = payload.v;
    Math::Vector3f normal = payload.normal;

    Math::Vector3f ambient;
    Math::Vector3f diffuse;
    Math::Vector3f specular;

    ambient = ka.cwise(amb_light_intensity);
    Color result_color;

    for(auto& light : lights){
        Math::Vector3f l = light.pos - point;
        float r_square = l.norm();
        r_square = std::pow(r_square, 2);
        l = l.normalized();

        diffuse = diffuse + kd.cwise(light.intensity / (r_square)) * std::max(0.0f, normal.dot(l));

        Math::Vector3f v = (eye_pos - point).normalized();
        Math::Vector3f h = (v + l).normalized();

        specular = specular + ks.cwise(light.intensity / (r_square)) * std::pow(std::max(0.0f, normal.dot(h)), p);
    }
    result_color = ambient + diffuse + specular;

    return result_color;
}

Color Shader::displacement_fragment_shader(const Vertex& payload, const Math::Vector3f& eye_pos){
    Math::Vector3f ka(0.005f, 0.005f, 0.005f);
    Math::Vector3f kd = payload.color.GetRGB();
    Math::Vector3f ks(0.7937f, 0.7937f, 0.7937f);

    auto l1 = Light{{20, 20, 20}, {500, 500, 500}};
    auto l2 = Light{{-20, 20, 0}, {500, 500, 500}};

    std::vector<Light> lights = {l1, l2};
    Math::Vector3f amb_light_intensity{10, 10, 10};

    float p = 150;

    Color color = payload.color;
    Math::Vector3f point = payload.v;
    Math::Vector3f normal = payload.normal;

    float kh = 0.2f, kn = 0.1f;
    float x = normal.x;
    float y = normal.y;
    float z = normal.z;

    Math::Vector3f t(x * y / std::sqrt(x * x + z * z), std::sqrt(x * x + z * z), z * y / std::sqrt(x * x + z * z));
    Math::Vector3f b = normal.cross(t);

    Math::Matrix TBN(3, 3);
    
    TBN[0][0] = t.x, TBN[0][1] = b.x, TBN[0][2] = normal.x;
    TBN[1][0] = t.y, TBN[1][1] = b.y, TBN[1][2] = normal.y;
    TBN[2][0] = t.z, TBN[2][1] = b.z, TBN[2][2] = normal.z;

    float u = payload.uv.x;
    float v = payload.uv.y;
    float w = payload.texture->width();
    float h = payload.texture->height();

    float dU = kh * kn * (payload.texture->GetColor(u + 1.0f / w, v).GetRGB().norm() - payload.texture->GetColor(u, v).GetRGB().norm());
    float dV = kh * kn * (payload.texture->GetColor(u, v + 1.0f / h).GetRGB().norm() - payload.texture->GetColor(u, v).GetRGB().norm());

    Math::Vector3f ln(-dU, -dV, 1.0f);
    normal = (TBN * ln).normalized();

    Math::Vector3f ambient;
    Math::Vector3f diffuse;
    Math::Vector3f specular;

    ambient = ka.cwise(amb_light_intensity);
    Color result_color;

    for(auto& light : lights){
        Math::Vector3f l = light.pos - point;
        float r_square = l.norm();
        r_square = std::pow(r_square, 2);
        l = l.normalized();

        diffuse = diffuse + kd.cwise(light.intensity / (r_square)) * std::max(0.0f, normal.dot(l));

        Math::Vector3f v = (eye_pos - point).normalized();
        Math::Vector3f h = (v + l).normalized();

        specular = specular + ks.cwise(light.intensity / (r_square)) * std::pow(std::max(0.0f, normal.dot(h)), p);
    }
    result_color = ambient + diffuse + specular;

    return result_color;
}
Color Shader::bump_fragment_shader(const Vertex& payload, const Math::Vector3f& eye_pos){
    Math::Vector3f ka(0.005f, 0.005f, 0.005f);
    Math::Vector3f kd = payload.color.GetRGB();
    Math::Vector3f ks(0.7937f, 0.7937f, 0.7937f);

    auto l1 = Light{{20, 20, 20}, {500, 500, 500}};
    auto l2 = Light{{-20, 20, 0}, {500, 500, 500}};

    std::vector<Light> lights = {l1, l2};
    Math::Vector3f amb_light_intensity{10, 10, 10};

    float p = 150;

    Color color = payload.color;
    Math::Vector3f point = payload.v;
    Math::Vector3f normal = payload.normal;

    float kh = 0.2f, kn = 0.1f;
    float x = normal.x;
    float y = normal.y;
    float z = normal.z;

    Math::Vector3f t(x * y / std::sqrt(x * x + z * z), std::sqrt(x * x + z * z), z * y / std::sqrt(x * x + z * z));
    Math::Vector3f b = normal.cross(t);

    Math::Matrix TBN(3, 3);
    
    TBN[0][0] = t.x, TBN[0][1] = b.x, TBN[0][2] = normal.x;
    TBN[1][0] = t.y, TBN[1][1] = b.y, TBN[1][2] = normal.y;
    TBN[2][0] = t.z, TBN[2][1] = b.z, TBN[2][2] = normal.z;

    float u = payload.uv.x;
    float v = payload.uv.y;
    float w = payload.texture->width();
    float h = payload.texture->height();

    float dU = kh * kn * (payload.texture->GetColor(u + 1.0f / w, v).GetRGB().norm() - payload.texture->GetColor(u, v).GetRGB().norm());
    float dV = kh * kn * (payload.texture->GetColor(u, v + 1.0f / h).GetRGB().norm() - payload.texture->GetColor(u, v).GetRGB().norm());

    Math::Vector3f ln(-dU, -dV, 1.0f);
    normal = (TBN * ln).normalized();
    Color result_color = normal;

    return result_color;
}