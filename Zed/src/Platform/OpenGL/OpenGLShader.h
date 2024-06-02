#pragma once

#include "Zed/Renderer/Shader.h"

// TODO:REMOVE!
typedef unsigned int GLenum;

namespace Zed {
    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string& filePath);
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~OpenGLShader();
        void Bind() const override;
        void Unbind() const override;

        void SetInt(const std::string& name, const int& value) override;
        // void SetFloat(const std::string& name, const float& value) override;
        // void SetFloat2(const std::string& name, const glm::vec2& value) override;
        // void SetFloat3(const std::string& name, const glm::vec3& value) override;
        // void SetFloat4(const std::string& name, const glm::vec4& value) override;
        // void SetMat3(const std::string& name, const glm::mat3& value) override;
        void SetMat4(const std::string& name, const glm::mat4& value) override;
    private:
        uint32_t m_RendererID;
        std::string ReadFile(const std::string& filePath);
        std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
        void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
    };
}