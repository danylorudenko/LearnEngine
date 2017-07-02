#ifndef __COMPONENT_H__
#define __COMPONENT_H__

class Entity;

class Component
{
public:
    Component                               ();

    Component                               (const Component& rhs);
    Component           operator=           (const Component& rhs);

    Component                               (Component&& rhs);
    Component           operator=           (Component&& rhs);

public:
    Entity&             GetOwner            ();

protected:
    void                SetOwner            (Entity* owner);

protected:
    Entity* owner_;

    friend class ComponentOwnerAttorney;
};

class ComponentOwnerAttorney
{
private:
    static void  SetComponentOwner(Component& instance, Entity* owner)
    {
        instance.SetOwner(owner);
    }

    friend class Entity;
};

#endif