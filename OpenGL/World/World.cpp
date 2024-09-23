#include "World.h"

#include "../../EditorUI/EntitiesListWindow.h"
#include "../Entities/Camera.h"
#include "../Entities/Entity.h"
#include "../Entities/Lights/PointLight.h"
#include "../Entities/Lights/SpotLight.h"
#include "../Entities/Lights/DirectionalLight.h"
#include "../Skybox/Skybox.h"
#include "ImGui/imgui.h"

World* World::m_instance = nullptr;
static Entity* m_selectedEntity;
World::World() :
m_skyboxActive(true),
m_window(EntitiesListWindow::GetInstance())
{
    m_selectedEntity = nullptr;
}

World::~World()
{
    //Delete all entities of the world
    for (Entity* entity : m_entities)
    {
        delete entity;
    }
    m_entities.clear();

    //Delete all lights of the world
    m_pointLights.clear();
    delete m_window;
    delete m_activeCamera;
    delete m_skybox;
}

//Singleton pattern
World* World::GetInstance()
{
    if (!m_instance)
    {
        m_instance = new World();
    }
    return m_instance;
}

//Draw all elements of the world
void World::Draw() const
{
    //Prepare all point lights of the world
    for (PointLight* pointLight : m_pointLights)
    {
        pointLight->Prepare();
    }

    //Prepare all spot lights of the world
    for (SpotLight* spotLight : m_spotLights)
    {
        spotLight->Prepare();
    }

    //Draw all entities of the world
    for (Entity* entity : m_entities)
    {
        entity->Draw();
    }

    //Draw skybox
    if(m_skybox && m_skyboxActive)
    {
        m_skybox->Draw();
    }
}

void World::SetWorldTick(bool _value)
{
    m_worldTickEnabled = _value;
}

void World::AddEntity(Entity* _entity)
{
    m_entities.push_back(_entity);
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

void World::SetSkybox(Skybox* _skybox)
{
    m_skybox = _skybox;
}

void World::SetSkybox(bool _value)
{
    m_skyboxActive = _value;
}

Light* World::GetLight(unsigned int _index)
{
    return m_lights[_index];
}

DirectionalLight* World::GetDirectionaLight() const
{
    return m_directionalLight;
}

bool World::GetWorldTick() const
{
    return m_worldTickEnabled;
}

//Initialization of world ticking
void World::Init()
{
    //Init all entities of the world
    for(Entity* entity : m_entities)
    {
        entity->Init();
    }
}

//End of world ticking
void World::End()
{
    //End all entities of the world
    for(Entity* entity : m_entities)
    {
        entity->End();
    }
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

//Tick all entities o the world
void World::Tick(float _deltaTime)
{
    for(Entity* entity : m_entities)
    {
        entity->Tick(_deltaTime);
    }
}
