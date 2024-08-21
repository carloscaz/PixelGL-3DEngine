#include "World.h"

#include "../../EditorUI/EntitiesListWindow.h"
#include "../Entities/Camera.h"
#include "../Entities/Entity.h"
#include "ImGui/imgui.h"

World* World::m_instance = nullptr;
static Entity* m_selectedEntity;
World::World()
{
    m_window = EntitiesListWindow::GetInstance();
    m_selectedEntity = nullptr; // Inicializar la entidad seleccionada como nullptr
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
    
    // ImGui::Begin("Entity List");
    //
    // for (Entity* entity : m_entities)
    // {
    //     bool isSelected = (entity == m_selectedEntity);
    //     if (ImGui::Selectable(entity->GetName().c_str(), isSelected))
    //     {
    //         m_selectedEntity = entity;
    //         m_window->SetObject(entity);
    //     }
    // }
    //
    // ImGui::End();
    // m_window->DrawWindow();
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

std::vector<Entity*>& World::GetEntities()
{
    return m_entities;
}

void World::Tick()
{
    m_activeCamera->Tick();
}
