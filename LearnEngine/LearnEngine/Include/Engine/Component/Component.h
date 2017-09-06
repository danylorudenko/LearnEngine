#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <utility>

class Entity;

template<typename TComponent> class ComponentFactory;

// Base abtract class for all components which can be attached to the 
class Component
{
    template<typename TComponent>
    friend class ComponentFactory;

public:

    using DestructionFunction = void(*)(Component*);

    Component                               (const Component& rhs) = delete;
    Component&          operator=           (const Component& rhs) = delete;
    Component                               (Component&& rhs) = delete;
    Component&          operator=           (Component&& rhs) = delete;

    virtual ~Component                      ();


    Entity&             GetOwner            ();

    virtual DestructionFunction GetDestructionFunc() = 0;

protected:

    // Default component setup, no owner, no system.
    Component();

    // Pure setting of the owner pointer.
    // Used in Component Registration mechanism.
    void                SetOwner            (Entity* owner);

protected:
    Entity* owner_;
};

#endif