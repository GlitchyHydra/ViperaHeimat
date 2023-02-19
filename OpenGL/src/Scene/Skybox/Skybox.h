#pragma once

#include <memory>
#include <string>

#include "Scene/GameObject.h"
#include "Scene/Camera/Camera.h"
#include "CubemapTexture.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Vipera {

	class Skybox
	{
	public:
		Skybox();
		~Skybox();

		bool Init(
			const std::string& Directory,
			const std::string& PosXFilename,
			const std::string& NegXFilename,
			const std::string& PosYFilename,
			const std::string& NegYFilename,
			const std::string& PosZFilename,
			const std::string& NegZFilename
		);

		void SetShader(Shader* shader);

		void Render(const std::shared_ptr<Camera>& camera,
			const glm::mat4& proj, const std::shared_ptr<Renderer>& pRenderer);

		Shader* GetShader() { return skyboxShader; }

	private:
		CubemapTexture* m_CubemapTex;
		GameObject* m_Mesh;
		Shader* skyboxShader;

		glm::vec3 scale { 4000.0f, 4000.0f, 4000.0f };
		glm::vec3 rotate { 0.0f, 0.0f, 0.0f };
	};

};