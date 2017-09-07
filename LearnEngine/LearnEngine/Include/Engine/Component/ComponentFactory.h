#ifndef __COMPONENT_FACTORY_H__
#define __COMPONENT_FACTORY_H__

#include <Engine\Entity\Entity.h>
#include <Engine\Component\GLObject\GLObject.h>
#include <Engine\RenderingSystem\RenderingSystem.h>
#include <Engine\Util\Memory\ObjectPool.h>

namespace Engine
{

template<typename TComponent>
class ComponentFactory
{
public:
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

private:
    /*static ObjectPool<TComponent>& ComponentPool()
    {
        static ObjectPool<TComponent>* component_pool_ = nullptr;

        return 
            *(component_pool_ != nullptr 
            ? component_pool_ 
            : (component_pool_ = new ObjectPool<TComponent>{ 20 }));
    }*/
};

template<>
class ComponentFactory<GLObject>
{
public:
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

    /*static ObjectPool<GLObject>& ComponentPool()
    {
        static ObjectPool<GLObject>* component_pool_ = nullptr;

        return 
            *(component_pool_ != nullptr
            ? component_pool_
            : (component_pool_ = new ObjectPool<GLObject>{ 20 }));
    }*/

};

} // namespace Engine

#endif