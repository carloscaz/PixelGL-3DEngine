#pragma once
#include <vector>

#include "../../Math/Vector3/Vector3.h"

class Skybox;
class SpotLight;
class PointLight;
class DirectionalLight;
class Light;
class Camera;
class EntitiesListWindow;
class ObjectDetailsWindow;
class Entity;

class World
{
private:
    World(); //Construtor private. Creation method with a singleton pattern
    
    std::vector<Entity*> m_entities;
    std::vector<Light*> m_lights;
    std::vector<PointLight*> m_pointLights;
    std::vector<SpotLight*> m_spotLights;
    DirectionalLight* m_directionalLight;
    static World* m_instance;
    EntitiesListWindow* m_window;

    Camera* m_activeCamera;
    float m_lightIntensity = 1.0f;
    Vector3 m_lightColor =  Vector3(1.0f, 1.0f,1.0f);

    Skybox* m_skybox;
    bool m_skyboxActive;

    bool m_worldTickEnabled = false;

public:
    ~World();
    static World* GetInstance();
    std::vector<Entity*>& GetEntities();
    std::vector<Light*>& GetLights();
    std::vector<PointLight*>& GetPointLights();
    std::vector<SpotLight*>& GetSpotLights();

    void AddEntity(Entity* _entity);
    void AddLight(Light* _light);
    void AddPointLight(PointLight* _light);
    void AddSpotLight(SpotLight* _light);
    void SetDirectionalLight(DirectionalLight* _light);
    void SetActiveCamera(Camera* _camera);
    void SetLightIntensity(float _intensity);
    void SetLightColor(const Vector3 _color);
    void SetSkybox(Skybox* _skybox);
    void SetSkybox(bool _value);
    void SetWorldTick(bool _value);

    void SaveEntitiesState() const;

    Camera* GetActiveCamera() const;
    float GetlightIntensity() const;
    Vector3 GetLightColor() const;
    Light* GetLight(unsigned int _index);
    DirectionalLight* GetDirectionaLight() const;
    bool GetWorldTick() const;

    void Init(); //Initialization of world ticking
    void End(); //End of world ticking
    void Tick(float _deltaTime);
    void Draw() const;
};
