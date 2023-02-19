#pragma once

#include <vector>

#include "abstractions/Shader.h"
#include "Scene/Camera/Camera.h"
#include "Scene/GameObject.h"
#include "Scene/Light/Light.h"
#include "Scene/Skybox/Skybox.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Vipera {
	class Scene
	{
	public: 
		Scene();
		~Scene();

		//void SetupSkybox();

		void AddGameObject(const std::shared_ptr<GameObject>& gameObject);
		void AddLight(const std::shared_ptr<Light>& lights);

		//Get Scene Attributes
		std::vector<std::shared_ptr<GameObject>>& GetGameObjects();
		const std::shared_ptr<Light>& GetLight() const;
		const std::shared_ptr<Camera>& GetCamera() const;
		//Skybox* GetSkybox() const { return skybox; }
		const glm::mat4& GetProj() const { return proj; }

	private:
		glm::mat4 proj = glm::scale(glm::perspective((float)glm::radians(45.0f), 1920.0f / 1080.0f, -1.0f, 100.0f), glm::vec3(1.0f, -1.0f, 1.0f));
		//glm::mat4 proj = glm::ortho(0.f, 1920.0f, 0.f, 1080.0f, -10.0f, 4000.0f);
		std::vector<std::shared_ptr<GameObject>> m_GameObjects;
		std::shared_ptr<Light> m_Light;
		std::shared_ptr<Camera> m_Camera;
		
	};
};