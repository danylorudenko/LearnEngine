#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <utility>

class Entity;


// Base abtract class for all components which can be attached to the 
class Component
{
public:

    Component                               (const Component& rhs) = delete;
    Component&          operator=           (const Component& rhs) = delete;
    Component                               (Component&& rhs) = delete;
    Component&          operator=           (Component&& rhs) = delete;

    virtual ~Component                      ();


    Entity&             GetOwner            ();

protected:

    // Default component setup, no owner, no system.
    Component();

    // Pure setting of the owner pointer.
    // Used in Component Registration mechanism.
    void                SetOwner            (Entity* owner);

    // Perform proper registration of the component in corresponding engine system.
    // Registration of performed when the component is attached to the Entity and the owner pointer was set.
    virtual void        RegisterInSystem    () = 0;

    // Perfrorm proper removal of the component from the corresponding engine system.
    // Removal is performed when the component is removed from Entity manually or when Enity is destroyed.
    virtual void        UnregisterFromSystem() = 0;


protected:
    Entity* owner_;

    friend class ComponentRegistrationAttorney;
};

#endif