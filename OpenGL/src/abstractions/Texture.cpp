#include "Texture.h"
#include <stb_image/stb_image.h>

#include <glad/glad.h>

void Texture::SetupTexture(const std::string& path)
{
	//stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_LocalBuffer) {
		stbi_image_free(m_LocalBuffer);
	}
}

Texture::Texture(const std::string& path, unsigned int slot)
	: m_RendererID(0), slot(slot),  m_FilePath(path), type(TextureType::NONE), m_LocalBuffer(nullptr),
	m_Width(0), m_Height(0), m_BPP(0)
{
	SetupTexture(path);
}

Texture::Texture(const std::string& path, unsigned int slot, const TextureType type)
	: m_RendererID(0), slot(slot), m_FilePath(path), type(type), m_LocalBuffer(nullptr),
	m_Width(0), m_Height(0), m_BPP(0) 
{
	SetupTexture(path);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_RendererID);
}

void Texture::Bind() const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::SetTexture(const std::shared_ptr<Shader>& shader) const
{
	switch (type) {
		case TextureType::NONE :{
				shader->SetUniform1i("u_Texture", slot);
			} break;
		case TextureType::DIFFUSE: {
				shader->SetUniform1i("Material.Diffuse", slot);
			} break;
		case TextureType::SPECULAR: {
				shader->SetUniform1i("Material.Specular", slot);
			} break;
		}
}