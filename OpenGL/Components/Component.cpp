#include "Component.h"

Entity* Component::GetOwner() const
{
    return m_owner;
}

void Component::SetOwner(Entity* _owner)
{
    m_owner = _owner;
}
