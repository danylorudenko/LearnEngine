#include "..\Include\Component\Component.h"

Entity& Component::GetOwner()
{
    return *owner_;
}

void Component::SetOwner(Entity * owner)
{
    owner_ = owner;
}
