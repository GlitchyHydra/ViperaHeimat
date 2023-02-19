#pragma once
#include <memory>

#include "Layer.h"
#include "Scene/GameObject.h"
#include "Scene/Skybox/Skybox.h"

namespace Vipera
{
	class LayerEditor : public Layer
	{
	public:
		LayerEditor(const std::string& name);

		void SetupSkybox();

		void Begin() const override;
		void End() const override;
		void Render() const override;

		void SetRenderer(std::shared_ptr<Renderer>& renderer) { m_Renderer = std::shared_ptr(renderer); }
		void SetScene(std::shared_ptr<Vipera::Scene>& scene) { m_Scene = std::shared_ptr(scene); }
		void SetDefaultShader(const std::shared_ptr<Shader>& shader) { m_Shader = shader; }

	private:
		std::shared_ptr<Renderer> m_Renderer;
		std::shared_ptr<Shader> m_Shader;

		std::shared_ptr<Vipera::Scene> m_Scene;
		std::vector<std::shared_ptr<GameObject>> m_GameObjects;
		std::shared_ptr<Vipera::Skybox> m_Skybox;
	};
}
