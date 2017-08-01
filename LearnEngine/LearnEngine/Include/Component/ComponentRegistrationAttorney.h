#ifndef __COMPONENT_REGISTRATION_ATTORNEY_H__
#define __COMPONENT_REGISTRATION_ATTORNEY_H__

#include <memory>

#include "Component.h"

// Attorney class to link the component registration system.
// Static methods wrap component's protected member functions.
class ComponentRegistrationAttorney
{
private:
    static void SetComponentOwner       (Component* component, Entity* owner);
    static void RegisterInSystem        (Component* component);
    static void UnregisterFromSystem    (Component* component);

    friend class Entity;
};

#endif