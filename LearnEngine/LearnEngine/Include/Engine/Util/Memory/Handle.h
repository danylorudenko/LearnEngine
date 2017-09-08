#ifndef __HANDLE_H__
#define __HANDLE_H__

namespace Engine
{

template<typename ID_type, typename FactoryType>
class Handle
{
public:
    using ID = ID_type;
    using obj_type = FactoryType::type;

    Handle              (ID object_id, FactoryType* owner_pool) : object_id_(object_id), owner_factory_(owner_pool) { }
    Handle              (const Handle& rhs) = default;
    Handle              (Handle&& rhs) = default;
    Handle&   operator= (const Handle& rhs) = default;
    Handle&   operator= (Handle&& rhs) = default;

    ID id() { return object_id_; }

    obj_type&       operator* ()        { return owner_factory_->Pool().ObjectRef(object_id_); }
    obj_type const& operator* () const  { return owner_factory_->Pool().ObjectRef(object_id_); }

    obj_type*       operator->()        { return owner_factory_->Pool().ObjectPtr(object_id_); }
    obj_type const* operator->() const  { return owner_factory_->Pool().ObjectPtr(object_id_); }

    void            DestroyObj() { owner_factory_->Release(object_id_); }

private:
    ID object_id_;
    FactoryType* owner_factory_;
};

} // namespace Engine

#endif