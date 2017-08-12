#include <stdexcept>
#include "..\Include\Component\Component.h"

Component::Component() : owner_(nullptr)
{

}

Component::~Component()
{

}

Entity& Component::GetOwner()
{
    return *owner_;
}

void Component::SetOwner(Entity* owner)
{
    owner_ = owner;
}