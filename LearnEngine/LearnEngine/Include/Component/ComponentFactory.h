#ifndef __COMPONENT_FACTORY_H__
#define __COMPONENT_FACTORY_H__

#include "..\Entity\Entity.h"
#include "GLObject\GLObject.h"

template<typename TComponent>
class ComponentFactory
{
    friend class Entity;

private:
    static TComponent* ConstructComponent(Entity* owner)
    {
        TComponent* component = new TComponent();
        component->SetOwner(owner);
        return new TComponent();
    }
};

template<>
class ComponentFactory<GLObject>
{
    friend class Entity;

private:
    static GLObject* ConstructComponent(Entity* owner)
    {
        GLObject* component = new GLObject();
        component->SetOwner(owner);
        return new GLObject();
    }
};

#endif