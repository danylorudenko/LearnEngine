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

    Component                               (const Component& rhs) = delete;
    Component&          operator=           (const Component& rhs) = delete;
    Component                               (Component&& rhs) = delete;
    Component&          operator=           (Component&& rhs) = delete;

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