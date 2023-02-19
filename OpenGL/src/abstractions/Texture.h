#pragma once

#include <memory>
#include <string>
#include "Shader.h"

enum class TextureType
{
	NONE = -1, DIFFUSE = 0, SPECULAR = 1
};

class Texture
{
private:
	unsigned int m_RendererID;
	unsigned int slot;
	std::string m_FilePath;
	TextureType type;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;

public:
	Texture(const std::string& path, unsigned int slot);
	Texture(const std::string& path, unsigned int slot, const TextureType type);
	~Texture();
	void Bind() const;
	void Unbind() const;
	void SetTexture(const std::shared_ptr<Shader>& shader) const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
private:
	void SetupTexture(const std::string& path);
};

