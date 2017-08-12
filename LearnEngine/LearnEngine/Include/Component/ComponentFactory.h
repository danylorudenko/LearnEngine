#ifndef __COMPONENT_FACTORY_H__
#define __COMPONENT_FACTORY_H__

#include "..\Entity\Entity.h"
#include "GLObject\GLObject.h"
#include "..\RenderingSystem\RenderingSystem.h"

template<typename TComponent>
class ComponentFactory
{
    friend class Entity;

private:
    static TComponent* ConstructComponent(Entity* owner)
    {
        TComponent* component = new TComponent();
        component->SetOwner(owner);
        return component;
    }

    static void DestroyComponent(TComponent* component)
    {
        delete component;
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
        RenderingSystem::Instance().AddToRenderingList(component);
        return component;
    }

    static void DestroyComponent(GLObject* component)
    {
        RenderingSystem::Instance().RemoveFromRenderingList(component);
        delete component;
    }
};

#endif