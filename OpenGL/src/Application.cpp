#include "Application.h"

#include <iostream>

#include "ImGUI/ImGuiLayer.h"
#include "Layer/LayerEditor.h"
#include "Scene/GameObject.h"

namespace Vipera {

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

    Application* Application::s_Application = nullptr;

    Application* CreateApplication()
    {
        return new Application();
    }

    Application::Application()
    {
        s_Application = this;
        
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

        renderer = std::make_shared<Renderer>();
        
        //m_Scene->SetupSkybox();

        auto editorLayer = new Vipera::LayerEditor("EditorLayer");
        PushLayer(editorLayer);
        auto mainUiLayer = new ImGuiLayer("UiEditorLayer");
        PushLayer(mainUiLayer);

        std::shared_ptr<Shader> shader = std::make_shared<Shader>("res/shaders/Model.shader");

        shader->Bind();
        std::shared_ptr<GameObject> gameObject = std::shared_ptr<GameObject>(new GameObject("res/models/E4/E 45 Aircraft_obj.obj"));
        m_Scene = std::make_shared<Scene>();
        m_Scene->AddGameObject(gameObject);

        std::shared_ptr<Light> lights = std::make_shared<Light>();
        m_Scene->AddLight(lights);
        lights->Init(*shader);

        shader->Unbind();

        editorLayer->SetRenderer(renderer);
        editorLayer->SetDefaultShader(shader);
        editorLayer->SetScene(m_Scene);
        editorLayer->SetupSkybox();

        ModelData* modelData = new ModelData(gameObject->GetTranslation(),
            gameObject->GetRotation(),
            gameObject->GetScale());

        mainUiLayer->PushData(modelData, m_Scene->GetLight().get());
        mainUiLayer->SetFramebuffer(m_Scene.get(), renderer->GetFrameBuffer());

        ImGuiLayer::Init();
    }

    Application::~Application()
    {

    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(Application::OnMouseMoved));
        //dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(Application::OnKeyReleased));

        //std::cout << e.ToString() << std::endl;

        /*for (auto it = m_LayerStack.end(); it != m_LayerStack.begin())
        {
            (*--it)->OnEvent(e);
            if (e.Handled)
                break;
        }*/
    }

	void Application::PushLayer(Vipera::Layer* layer)
	{
        m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Vipera::Layer* layer)
	{
        m_LayerStack.PopLayer(layer);
	}

    void Application::CheckForMoveCamera()
    {
        if (IsKeyPressed(GLFW_KEY_W))
            m_Scene->GetCamera()->Forward();
        if (IsKeyPressed(GLFW_KEY_S))
            m_Scene->GetCamera()->Back();
        if (IsKeyPressed(GLFW_KEY_A))
            m_Scene->GetCamera()->Left();
        if (IsKeyPressed(GLFW_KEY_D))
            m_Scene->GetCamera()->Right();

        auto window = static_cast<GLFWwindow*>(GetWindow().GetNativeWindow());
        if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS && !mousePosCalculated)
        {
            double x, y;
            glfwGetCursorPos(window, &x, &y);
            mouseEndPos = glm::vec2((float)x, (float)y);
            std::cout << "Mouse" << std::endl;
            float deltaX = mouseEndPos.x - mouseBeginPos.x;
            float deltaY = mouseEndPos.y - mouseBeginPos.y;
            std::cout << "X: " << deltaX << std::endl;
            std::cout << "Y: " << deltaY << std::endl;

            mouseBeginPos = mouseEndPos;

            float sensitivity = 0.1f;
            glm::vec2 rotationVec = glm::vec2(deltaX * sensitivity, deltaY * sensitivity);
            m_Scene->GetCamera()->SetRotation(rotationVec);

            mousePosCalculated = true;
            //glm::rotate()
        }
    }

    bool Application::OnMouseMoved(MouseMovedEvent& event)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        
        auto state = glfwGetKey(window, GLFW_KEY_LEFT_ALT);
        if (state == GLFW_PRESS && mousePosCalculated)
        {
            mouseBeginPos = glm::vec2(event.GetX(), event.GetY());
            mousePosCalculated = false;
        }
        return false;
    }

    void Application::Run()
	{
        while (m_Running)
        {
            CheckForMoveCamera();
            
            for (Layer* layer : m_LayerStack)
            {
                layer->Begin();
                layer->Render();
                layer->End();
            }

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }

    bool Application::IsKeyPressed(int button)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, button);
        return state == GLFW_PRESS;
    }

}

int main(int argc, char** argv)
{
    auto app = Vipera::CreateApplication();
    app->Run();
    delete app;
    return 0;
}
