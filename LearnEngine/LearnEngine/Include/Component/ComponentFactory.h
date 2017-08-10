#ifndef __COMPONENT_FACTORY_H__
#define __COMPONENT_FACTORY_H__

#include "..\Entity\Entity.h"

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

#endif