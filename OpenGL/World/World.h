#pragma once
#include <vector>

#include "../../Math/Vector3/Vector3.h"


class Light;
class Camera;
class EntitiesListWindow;
class ObjectDetailsWindow;
class Entity;

class World
{
private:
    std::vector<Entity*> m_entities;
    std::vector<Light*> m_lights;
    std::vector<const char*> m_entitiesNames;
    World();
    static World* m_instance;
    EntitiesListWindow* m_window;

    Camera* m_activeCamera;
    float m_lightIntensity = 1.0f;
    Vector3 m_lightColor =  Vector3(1.0f, 1.0f,1.0f);

public:
    static World* GetInstance();
    
    void Draw();
    void AddEntity(Entity* _entity);
    void AddLight(Light* _light);

    void SetActiveCamera(Camera* _camera);
    Camera* GetActiveCamera() const;
    void SetLightIntensity(float _intensity);
    float GetlightIntensity() const;
    Vector3 GetLightColor() const;
    void SetLightColor(const Vector3 _color);
    Light* GetLight(unsigned int _index);

    std::vector<Entity*>& GetEntities();

    void Tick();
};
