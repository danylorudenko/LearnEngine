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
    virtual Component&  operator=           (const Component& rhs) = 0;

private:
    Component                               ();
    Component                               (const Component& rhs);
    Component                               (Component&& rhs);

public:
    Entity&             GetOwner            ();

protected:
    void                SetOwner            (Entity* owner);

protected:
    Entity* owner_;

    friend class ComponentOwnerAttorney;
};

/* 
    Attorney class to access initializaton 
    and constuction of componets from the entities.
*/
class ComponentOwnerAttorney
{
private:
    static void  SetComponentOwner(Component& instance, Entity* owner)
    {
        instance.SetOwner(owner);
    }

    static Component CreateComponent()
    {
        return Component();
    }

    static Component CopyComponent(const Component& rhs)
    {
        return Component(rhs);
    }

    static Component CopyComponent(Component&& rhs)
    {
        return Component(std::move(rhs));
    }

    friend class Entity;
};

#endif