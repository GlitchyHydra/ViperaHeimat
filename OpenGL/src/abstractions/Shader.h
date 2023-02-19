#pragma once

#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	unsigned int m_RendererID;
	const std::string& m_FilePath;
	std::unordered_map<std::string, int> uniformLocationMap;
public:
	Shader(const std::string& filepath);

	Shader(const Shader& rhs) = delete;
	Shader(Shader&& rhs) = delete;
	Shader& operator=(const Shader& rhs) = delete;
	Shader& operator=(Shader&& rhs) = delete;

	~Shader();

	void Bind() const;
	void Unbind() const;

	//set uniforms
	void SetUniform1ui(const std::string& name, unsigned int v);
	void SetUniform1i(const std::string& name, int v);
	void SetUniform1f(const std::string& name, float v);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform4f(const std::string& name, float v0, float v1, float f2, float f3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
	ShaderProgramSource ParseShader();
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
private:
	int GetUniformLocation(const std::string& name);
};


