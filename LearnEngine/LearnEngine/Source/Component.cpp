#include <stdexcept>
#include <Engine\Component\Component.h>

namespace Engine
{

Component::Component() : 
    owner_(nullptr)
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

} // namespace Engine