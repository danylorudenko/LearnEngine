#include "..\Include\Component\Component.h"
#include "..\Include\Entity\Entity.h"

Entity& Component::GetOwner()
{
    return *owner_;
}

void Component::SetOwner(Entity * owner)
{
    owner_ = owner;
}

Entity::Entity()
{

}

Entity::Entity(const Entity & rhs) : components_(rhs.components_)
{
}
