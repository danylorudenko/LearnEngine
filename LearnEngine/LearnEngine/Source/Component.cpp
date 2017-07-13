#include <stdexcept>
#include "..\Include\Component\Component.h"

Component::Component() : owner_(nullptr), in_system_(false)
{

}

Component::Component(const Component& rhs) : owner_(nullptr), in_system_(false)
{

}

Component& Component::operator=(const Component& rhs)
{

}

Component::Component(Component&& rhs) : owner_(nullptr), in_system_(false)
{
    if (rhs.in_system_) {
        throw std::logic_error("Can't move components which are used in engine systems.");
    }
}

Component& Component::operator=(Component&& rhs)
{
    if (rhs.in_system_) {
        throw std::logic_error("Can't move-assign components which are used in engine systems.");
    }
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