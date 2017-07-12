#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <utility>

class Entity;

/*
    Base abtract class for all components which can be attached to the 
*/
class Component
{
public:
    // Default component setup, no owner, no system.
    Component                               ();

    // Copy-construcion is allowed, but without owners and without registration.
    // Owner is set no nullptr.
    Component                               (const Component& rhs);

    // Copying is allowed, but without owners and registration.
    Component&          operator=           (const Component& rhs);
    
    // Move-construction is only allowed, when the component is not registered in engine systems.
    // Owner is set to nullptr.
    Component                               (Component&& rhs);

    // Move-assignment is only allowed, when the component is not registered in engine systems. 
    Component&          operator=           (Component&& rhs);

    virtual ~Component                      ();


    Entity&             GetOwner            ();

protected:
    void                SetOwner            (Entity* owner);
    virtual void        RegisterInSystem    () = 0;
    virtual void        UnregisterFromSystem() = 0;


protected:
    Entity* owner_;
    bool    in_system_;

    friend class ComponentRegistrationAttorney;
};

#endif