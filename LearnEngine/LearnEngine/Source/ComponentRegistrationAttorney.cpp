#include "..\Include\Component\ComponentRegistrationAttorney.h"

void ComponentRegistrationAttorney::SetComponentOwner(Component* component, Entity* owner)
{
    component->SetOwner(owner);
}

void ComponentRegistrationAttorney::RegisterInSystem(Component* component)
{
    component->RegisterInSystem();
}

void ComponentRegistrationAttorney::UnregisterFromSystem(Component* component)
{
    component->UnregisterFromSystem();
}