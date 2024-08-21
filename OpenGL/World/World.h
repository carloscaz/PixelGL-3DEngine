#pragma once
#include <vector>

class Camera;
class EntitiesListWindow;
class ObjectDetailsWindow;
class Entity;

class World
{
private:
    std::vector<Entity*> m_entities;
    std::vector<const char*> m_entitiesNames;
    World();
    static World* m_instance;
    EntitiesListWindow* m_window;

    Camera* m_activeCamera;
public:
    static World* GetInstance();
    
    void Draw();
    void AddEntity(Entity* _entity);

    void SetActiveCamera(Camera* _camera);
    Camera* GetActiveCamera() const;

    std::vector<Entity*>& GetEntities();
};
