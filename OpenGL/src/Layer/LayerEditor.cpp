#include "LayerEditor.h"

#include "Scene/Scene.h"

namespace Vipera
{
	LayerEditor::LayerEditor(const std::string& name)
		: Layer(name)
	{
	}

	void LayerEditor::SetupSkybox()
	{
		if (!m_Scene)
		{
			//TODO debug no scene defined
			return;
		}

		m_Skybox = std::make_shared<Skybox>();
		m_Skybox->SetShader(new Shader("res/shaders/Skybox.shader"));

		m_Skybox->GetShader()->Bind();
		m_Skybox->Init(".",
			"res/skybox/sp3right.jpg",
			"res/skybox/sp3left.jpg",
			"res/skybox/sp3top.jpg",
			"res/skybox/sp3bot.jpg",
			"res/skybox/sp3front.jpg",
			"res/skybox/sp3back.jpg");
		m_Skybox->GetShader()->Unbind();
	}

	void LayerEditor::Begin() const
	{

	}

	void LayerEditor::End() const
	{

	}

	void LayerEditor::Render() const
	{
		glEnable(GL_DEPTH_TEST);

		m_Renderer->GetFrameBuffer()->Bind();
		m_Renderer->Clear();

		m_Skybox->Render(m_Scene->GetCamera(), m_Scene->GetProj(), m_Renderer);
		
		m_Shader->Bind();

		m_Scene->GetCamera()->SetEyeInShader(m_Shader);
		m_Scene->GetLight()->SetDirectLights(m_Shader);
		m_Scene->GetLight()->SetPointLights(m_Shader);

		auto& view = m_Scene->GetCamera()->GetView();
		auto& proj = m_Scene->GetProj();
		auto mvp = proj;

		auto& gameObjects = m_Scene->GetGameObjects();
		//TODO replace it with
		//auto& gameObjects = m_GameObjects;

		for (auto& gameObj : gameObjects)
		{
			bool toRender = gameObj->IsNeedToRender();
			if (!toRender)
			{
				continue;
			}

			//set mvp
			gameObj->SetModelTrans(m_Shader.get());
			auto tran = gameObj->GetTransform();
			mvp = proj * view * tran;
			m_Shader->SetUniformMat4f("u_MVP", mvp);


			const std::vector<Texture*>& textures = gameObj->GetTextures();

			for (auto& mesh : gameObj->GetMeshes())
			{
				mesh.va.Bind();
				if (textures.size() > 0) 
				{
					textures[mesh.matInd]->Bind();
					textures[mesh.matInd]->SetTexture(m_Shader);
				}
				m_Renderer->Draw(mesh.ib);
				mesh.va.Unbind();
			}
		}
		m_Shader->Unbind();

		m_Renderer->GetFrameBuffer()->Unbind();
	}

}

