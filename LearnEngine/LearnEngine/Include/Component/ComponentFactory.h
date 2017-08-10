#ifndef __COMPONENT_FACTORY_H__
#define __COMPONENT_FACTORY_H__

#include "..\Entity\Entity.h"
#include "..\Component\Light\Light.h"
#include "..\Component\GLObject\GLObject.h"

template<typename TComponent>
class ComponentFactory
{
private:
    static TComponent* ConstructComponent()
    {
        return new TComponent();
    }

    friend class Entity;
};

template<>
class ComponentFactory<GLObject>
{
private:
    static TComponent* ConstructComponent()
    {
        return new GLObject();
    }
};

template<>
class ComponentFactory<Light>
{
private:
    static TComponent* ConstructComponent()
    {
        return new Light();
    }
};

#endif