#ifndef __COMPONENT_FACTORY_H__
#define __COMPONENT_FACTORY_H__

#include <Engine\Entity\Entity.h>
#include <Engine\Component\Component.h>
#include <Engine\Util\Memory\ObjectPool.h>
#include <Engine\Util\Memory\Handle.h>

namespace Engine
{

template<
    typename TComponent,
    typename ID_type,
    template <typename> PoolType,
    template <typename> HandleType
>
class ComponentFactory
{
public:
    using component_t = TComponent;
    using id_t = ID_type;
    using pool_t = PoolType<TComponent, id_t>;
    using handle_t = HandleType<id_t, pool_t>;

    ComponentFactory() { }

    handle_t* ConstructComponent(Entity* owner) { return handle_t{ object_pool_.NewObject(), this }; }

    void DestroyComponent(handle_t* component) { object_pool_.Release(component.id()) };

private:
    pool_t object_pool_;
};

} // namespace Engine

#include <Engine\Inl\ComponentFactory.inl>

#endif