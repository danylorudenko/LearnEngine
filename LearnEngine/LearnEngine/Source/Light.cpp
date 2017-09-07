#include <Engine\Component\Light\Light.h>
#include <Engine\Component\ComponentFactory.h>

namespace Engine
{

Light::Light()
{
}

Component::DestructionFunction Light::GetDestructionFunc()
{
    return [](Component* this_component) {
        ComponentFactory<Light>::DestroyComponent(dynamic_cast<Light*>(this_component));
    };
}

} // namespace Engine
