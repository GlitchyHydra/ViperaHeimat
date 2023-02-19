#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "imgui.h"
#include "Layer/Layer.h"
#include "Scene/Light/Light.h"

#include "Scene/Scene.h"
#include "abstractions/OpenGLFramebuffer.h"

namespace Vipera
{

	class LayerStack;

	struct ModelData
	{
		glm::vec3& translation;
		glm::vec3& rotation;
		glm::vec3& scale;

		ModelData(glm::vec3& t, glm::vec3& r, glm::vec3& s)
			: translation(t), rotation(r), scale(s)
		{}
	};

	struct LightData
	{
		std::vector<DirectionalLight>& directionalLights;
		std::vector<PointLight>& pointLights;

	};

	class ImGuiLayer : public Vipera::Layer
	{
	public: 
		ImGuiLayer(const std::string name);
		virtual ~ImGuiLayer();

		static void Init();
		static void Shutdown();

		virtual void Begin() const override;
		virtual void End() const override;
		virtual void Render() const override;

		void PushData(ModelData* data, Light* light);
		void SetFramebuffer(Scene* pScene, OpenGLFramebuffer* fbuffer);
	private:
		void RenderDockspace() const;
		void RenderViewport() const;
		void RenderMainWindow() const;
		void RenderDataWindow() const;

		//dockspace window
		bool p_open = true;

		//editor game objects data
		ModelData* m_ModelData;
		LightData* m_LightData;

		//viewport
		mutable ImVec2 size;
		Scene* mScene;
		OpenGLFramebuffer* mFramebuffer;

		mutable bool show;
	};
	
}