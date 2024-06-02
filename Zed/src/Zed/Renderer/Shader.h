#pragma once
#include <string>
#include <stdint.h>
#include <glm/glm.hpp>
namespace Zed {
    class Shader {
    public:
        ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetInt(const std::string& name, const int& value) = 0;
        // 预留几个接口
        // virtual void SetFloat(const std::string& name, const float& value) = 0;
        // virtual void SetFloat2(const std::string& name, const glm::vec2& value) = 0;
        // virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
        // virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
        // virtual void SetMat3(const std::string& name, const glm::mat3& value) = 0;
        virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

        static Shader* Create(const std::string& filePath);
        static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
    };
}