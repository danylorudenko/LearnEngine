#include "Light.h"
#include "..\ComponentFactory.h"

Light::Light()
{
}

Component::DestructionFunction Light::GetDestructionFunc()
{
    return [](Component* this_component) {
        ComponentFactory<Light>::DestroyComponent(dynamic_cast<Light*>(this_component));
    };
}
