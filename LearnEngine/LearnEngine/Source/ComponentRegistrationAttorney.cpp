#include "..\Include\Component\ComponentRegistrationAttorney.h"

void ComponentRegistrationAttorney::SetComponentOwner(std::shared_ptr<Component> component, Entity* owner)
{
    component->SetOwner(owner);
}

void ComponentRegistrationAttorney::RegisterInSystem(std::shared_ptr<Component> component)
{
    component->RegisterInSystem();
}

void ComponentRegistrationAttorney::UnregisterFromSystem(std::shared_ptr<Component> component)
{
    component->UnregisterFromSystem();
}