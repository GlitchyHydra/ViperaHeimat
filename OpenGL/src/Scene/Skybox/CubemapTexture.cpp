
#include "CubemapTexture.h"

#include <stb_image/stb_image.h>

namespace Vipera {

	static const GLenum types[6] = { GL_TEXTURE_CUBE_MAP_POSITIVE_X,
								  GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
								  GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
								  GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
								  GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
								  GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };

	CubemapTexture::CubemapTexture(const std::string& Directory,
		const std::string& PosXFilename,
		const std::string& NegXFilename,
		const std::string& PosYFilename,
		const std::string& NegYFilename,
		const std::string& PosZFilename,
		const std::string& NegZFilename)
	{
		std::string::const_iterator it = Directory.end();
		it--;
		std::string BaseDir = (*it == '/') ? Directory : Directory + "/";

		m_fileNames[0] = BaseDir + PosXFilename;
		m_fileNames[1] = BaseDir + NegXFilename;
		m_fileNames[2] = BaseDir + PosYFilename;
		m_fileNames[3] = BaseDir + NegYFilename;
		m_fileNames[4] = BaseDir + PosZFilename;
		m_fileNames[5] = BaseDir + NegZFilename;

		m_textureObj = 0;
	}

	CubemapTexture::~CubemapTexture()
	{
		if (m_textureObj != 0) {
			glDeleteTextures(1, &m_textureObj);
		}
	}

	bool CubemapTexture::Load()
	{
		glGenTextures(1, &m_textureObj);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureObj);
		int m_Width = 560;
		int m_Height = 560;
		int m_BPP = 4;

		for (unsigned int i = 0; i < 6; i++)
		{
			unsigned char* m_LocalBuffer = stbi_load(m_fileNames[i].c_str(), &m_Width, &m_Height, &m_BPP, 4);
			glTexImage2D(types[i], 0, GL_RGB, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);

			if (m_LocalBuffer) {
				stbi_image_free(m_LocalBuffer);
			}
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		return false;
	}

	void CubemapTexture::Bind(GLenum TextureUnit)
	{
		glActiveTexture(TextureUnit);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureObj);
	}
}