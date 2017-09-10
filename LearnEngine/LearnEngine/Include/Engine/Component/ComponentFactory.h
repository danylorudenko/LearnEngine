#ifndef __COMPONENT_FACTORY_H__
#define __COMPONENT_FACTORY_H__

#include <Engine\Util\Constants.h>
#include <Engine\Entity\Entity.h>
#include <Engine\Component\Component.h>
#include <Engine\Util\Memory\ObjectPool.h>
#include <Engine\Util\Memory\Handle.h>

namespace Engine
{

template<
    typename TComponent,
    template <typename, typename> typename PoolType,
    template <typename, typename> typename HandleType
>
class ComponentFactory
{
public:
    using component_t = TComponent;
    using id_t = CONSTANTS::HANDLE_ID_TYPE;
    using pool_t = PoolType<component_t, id_t>;
    using handle_t = HandleType<id_t, pool_t>;

    ComponentFactory() { }

    handle_t ConstructComponent(Entity* owner) { return handle_t{ object_pool_.NewObject(), this }; }

    void DestroyComponent(handle_t* component) { object_pool_.Release(component.id()) };

    pool_t&         Pool()          { return object_pool_; }
    pool_t const&   Pool() const    { return object_pool_; }

private:
    pool_t object_pool_;
};

} // namespace Engine

#include <Engine\Inl\ComponentFactory.inl>

#endif