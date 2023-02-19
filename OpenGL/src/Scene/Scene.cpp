#include "Scene.h"

#include <iostream>

namespace Vipera {
    
    Scene::Scene()
	    : m_Camera(std::make_shared<Camera>())
    {

    }
    
    Scene::~Scene()
    {
    }
    
    void Scene::AddGameObject(const std::shared_ptr<GameObject>& gameObject)
    {
        m_GameObjects.emplace_back(std::shared_ptr(gameObject));
    }

    void Scene::AddLight(const std::shared_ptr<Light>& lights)
    {
        m_Light = std::shared_ptr(lights);
    }

    std::vector<std::shared_ptr<GameObject>>& Scene::GetGameObjects()
    {
        return m_GameObjects;
    }

    const std::shared_ptr<Light>& Scene::GetLight() const
    {
        return m_Light;
    }

    const std::shared_ptr<Camera>& Scene::GetCamera() const
    {
        return m_Camera;
    }
};