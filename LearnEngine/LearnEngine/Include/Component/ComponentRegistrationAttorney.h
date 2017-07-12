#ifndef __COMPONENT_REGISTRATION_ATTORNEY_H__
#define __COMPONENT_REGISTRATION_ATTORNEY_H__

#include <memory>

#include "Component.h"

class ComponentRegistrationAttorney
{
private:
    static void SetComponentOwner(std::shared_ptr<Component> component, Entity* owner);
    static void RegisterInSystem(std::shared_ptr<Component> component);
    static void UnregisterFromSystem(std::shared_ptr<Component> component);

    friend class Entity;
};

#endif