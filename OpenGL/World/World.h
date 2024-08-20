#pragma once
#include <vector>

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
public:
    static World* GetInstance();
    
    void Draw();
    void AddEntity(Entity* _entity);

    std::vector<Entity*>& GetEntities();
};
