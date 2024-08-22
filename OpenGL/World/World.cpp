#include "World.h"

#include "../../EditorUI/EntitiesListWindow.h"
#include "../Entities/Camera.h"
#include "../Entities/Entity.h"
#include "../Entities/Lights/Light.h"
#include "ImGui/imgui.h"

World* World::m_instance = nullptr;
static Entity* m_selectedEntity;
World::World()
{
    m_window = EntitiesListWindow::GetInstance();
    m_selectedEntity = nullptr;
}

World::~World()
{
    for (Entity* entity : m_entities)
    {
        delete entity;
    }
    m_entities.clear();
    m_lights.clear();
    m_pointLights.clear();
}

World* World::GetInstance()
{
    if (!m_instance)
    {
        m_instance = new World();
    }
    return m_instance;
}

void World::Draw()
{
    for (Entity* entity : m_entities)
    {
        entity->Draw();
    }
}

void World::AddEntity(Entity* _entity)
{
    m_entities.push_back(_entity);
    m_entitiesNames.push_back(_entity->GetName().c_str());
}

void World::AddLight(Light* _light)
{
    m_lights.push_back(_light);
}

void World::AddPointLight(PointLight* _light)
{
    m_pointLights.push_back(_light);
}

void World::AddSpotLight(SpotLight* _light)
{
    m_spotLights.push_back(_light);
}

void World::SetDirectionalLight(DirectionalLight* _light)
{
    m_directionalLight = _light;
}

void World::SetActiveCamera(Camera* _camera)
{
    m_activeCamera = _camera;
}

Camera* World::GetActiveCamera() const
{
    return m_activeCamera;
}

void World::SetLightIntensity(float _intensity)
{
    m_lightIntensity = _intensity;
}

float World::GetlightIntensity() const
{
    return m_lightIntensity;
}

Vector3 World::GetLightColor() const
{
    return m_lightColor;
}

void World::SetLightColor(const Vector3 _color)
{
    m_lightColor = _color;
}

Light* World::GetLight(unsigned int _index)
{
    return m_lights[_index];
}

DirectionalLight* World::GetDirectionaLight() const
{
    return m_directionalLight;
}

std::vector<Entity*>& World::GetEntities()
{
    return m_entities;
}

std::vector<Light*>& World::GetLights()
{
    return m_lights;
}

std::vector<PointLight*>& World::GetPointLights()
{
    return m_pointLights;
}

std::vector<SpotLight*>& World::GetSpotLights()
{
    return m_spotLights;
}

void World::Tick()
{
    m_activeCamera->Tick();
}
