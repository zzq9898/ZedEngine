#pragma once
#include <string>
#include <stdint.h>
#include <glm/glm.hpp>
namespace Zed {
    class Shader {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        void SetInt(const std::string& name, const int& value);
        void SetMat4(const std::string& name, const glm::mat4& matrix);
    private:
        uint32_t m_RendererID;
    };
}