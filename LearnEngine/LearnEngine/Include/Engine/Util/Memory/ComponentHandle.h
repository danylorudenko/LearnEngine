#ifndef __COMPONENT_HANDLE_H__
#define __COMPONENT_HANDLE_H__

#include <Engine\Util\Memory\Handle.h>

namespace Engine
{

template<typename ID_type, typename FactoryType>
class ComponentHandle : public Handle
{
public:
    using ID = ID_type;
    using obj_type = FactoryType::type;

    ComponentHandle              (ID object_id, FactoryType* owner_factory) : object_id_(object_id), owner_factory_(owner_factory) { }
    ComponentHandle              (const ComponentHandle& rhs) = default;
    ComponentHandle              (ComponentHandle&& rhs) = default;
    ComponentHandle&   operator= (const ComponentHandle& rhs) = default;
    ComponentHandle&   operator= (ComponentHandle&& rhs) = default;

    ID id() { return object_id_; }

    obj_type&       operator* ()        { return owner_factory_->Pool().ObjectRef(object_id_); }
    obj_type const& operator* () const  { return owner_factory_->Pool().ObjectRef(object_id_); }

    virtual obj_type*       operator->()       override { return owner_factory_->Pool().ObjectPtr(object_id_); }
    virtual obj_type const* operator->() const override { return owner_factory_->Pool().ObjectPtr(object_id_); }

    virtual void            DestroyObj() override { owner_factory_->Pool().Release(object_id_); }

private:
    ID object_id_;
    FactoryType* owner_factory_;
};

} // namespace Engine

#endif