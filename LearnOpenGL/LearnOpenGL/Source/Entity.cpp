#include "..\Include\Entity\Entity.h"
#include "..\Include\Component\ComponentRegistrationAttorney.h"

Entity::Entity()
{

}

Entity::Entity(const Entity & rhs) : components_(rhs.components_)
{

}
