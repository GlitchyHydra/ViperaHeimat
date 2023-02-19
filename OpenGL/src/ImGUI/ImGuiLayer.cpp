#include "ImGuiLayer.h"

#include <Layer/LayerStack.h>

#include "Application.h"

#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

namespace Vipera {

	ImGuiLayer::ImGuiLayer(const std::string name)
		: Layer(name)
	{}

	ImGuiLayer::~ImGuiLayer()
	{
		delete m_ModelData;
		delete m_LightData;
	}

	void ImGuiLayer::Init()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

		//ImGui::ShowDemoWindow();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::Shutdown()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::Begin() const
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::Render() const
	{
		ImGuiIO& io = ImGui::GetIO();
		RenderDockspace();
		RenderMainWindow();
		RenderDataWindow();
		RenderViewport();
		
		ImGui::Render();
		
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::RenderDockspace() const
	{
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background 
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("###DockSpace", const_cast<bool*>(&p_open), window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}
		else
		{
			//ShowDockingDisabledMessage();
		}

		ImGui::End();
	}

	void ImGuiLayer::RenderViewport() const
	{
		ImGui::Begin(GetName().c_str(), &show,
			ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

		auto tex = mFramebuffer->GetColorAttachmentTexID();

		ImGui::Image((void*)tex, size);
		if (size.x != ImGui::GetWindowWidth() || size.y != ImGui::GetWindowHeight())
		{
			size.x = ImGui::GetWindowWidth();
			size.y = ImGui::GetWindowHeight();
			mFramebuffer->SetNewParametrs(size.x, size.y);
		}

		ImGui::End();
	}

	void ImGuiLayer::RenderMainWindow() const
	{
		ImGui::Begin("Main window");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	void ImGuiLayer::RenderDataWindow() const
	{
		ImGui::Begin("Lights");

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		//GameObject Transforms
		ImGui::Text("GameObject");
		ImGui::SliderFloat3("Translation", &m_ModelData->translation.x, 0.0f, 1920.0f);
		ImGui::SliderFloat3("Scale", &m_ModelData->scale.x, 1.0f, 1000.0f);
		ImGui::SliderFloat3("Rotation", &m_ModelData->rotation.x, 0.0f, 359.0f);
		//Light Transforms
		ImGui::Text("Directional Lights");
		for (unsigned int i = 0; i < m_LightData->directionalLights.size(); i++)
		{
			DirectionalLight& light = m_LightData->directionalLights[i];
			ImGui::Text("Directional Light " + i);
			ImGui::SliderFloat("Ambinet Intensity" + i, &light.AmbientIntensity, 0.0f, 20.0f);
			ImGui::SliderFloat("Diffuse Intensity" + i, &light.DiffuseIntensity, 0.0f, 20.0f);
			ImGui::SliderFloat("SpecularIntensity" + i, &light.SpecularIntensity, 0.0f, 20.0f);
			ImGui::SliderFloat4("Color " + i, &light.Color.x, 0.0f, 1.0f);
			ImGui::SliderFloat3("Direction" + i, &light.Direction.x, 0.0f, 1920.0f);
		}


		ImGui::Text("Points Lights");
		for (unsigned int i = 0; i < m_LightData->pointLights.size(); i++)
		{
			PointLight& light = m_LightData->pointLights[i];
			ImGui::Text("Point Light " + i);
			ImGui::SliderFloat("Point Light Ambinet Intensity" + i, &light.AmbientIntensity, 0.0f, 20.0f);
			ImGui::SliderFloat("Point Light Diffuse Intensity" + i, &light.DiffuseIntensity, 0.0f, 20.0f);
			ImGui::SliderFloat("Point Light SpecularIntensity" + i, &light.SpecularIntensity, 0.0f, 20.0f);
			ImGui::SliderFloat4("Point Light Color " + i, &light.Color.x, 0.0f, 1.0f);
			ImGui::SliderFloat3("Position" + i, &light.Position.x, 0.0f, 1920.0f);
		}

		ImGui::End();
	}

	void ImGuiLayer::End() const
	{
	}

	void ImGuiLayer::PushData(ModelData* data, Light* light)
	{
		m_ModelData = data;
		m_LightData = new LightData
		{
			light->GetDirectLight(),
			light->GetPointLight()
		};
	}

	void ImGuiLayer::SetFramebuffer(Scene* pScene, OpenGLFramebuffer* fbuffer)
	{
		mScene = pScene;
		mFramebuffer = fbuffer;
		size.x = mFramebuffer->GetSpecification().Width;
		size.y = mFramebuffer->GetSpecification().Height;
		show = true;
	}
}
