#include <stdexcept>
#include <Engine\Component\Component.h>

namespace Engine
{

Component::Component(Entity* owner) : 
    owner_(owner)
{

}

Component::~Component()
{

}

Entity& Component::GetOwner()
{
    return *owner_;
}

} // namespace Engine