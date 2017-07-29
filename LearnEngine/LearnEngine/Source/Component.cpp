#include <stdexcept>
#include "..\Include\Component\Component.h"

Component::Component() : owner_(nullptr), in_system_(false)
{

}

Component::~Component()
{
    UnregisterFromSystem();
}

Entity& Component::GetOwner()
{
    return *owner_;
}

void Component::SetOwner(Entity* owner)
{
    owner_ = owner;
}

void Component::RegisterInSystem()
{
    if (owner_ == nullptr) {
        throw std::logic_error("Can't register component which is not attached to any entity.");
    }
    in_system_ = true;
}

void Component::UnregisterFromSystem()
{
    in_system_ = false;
    owner_ = nullptr;
}