#ifndef __HANDLE_H__
#define __HANDLE_H__

namespace Engine
{

template<typename ID_type, typename PoolType>
class Handle
{
public:
    using ID = ID_type;
    using obj_type = PoolType::type;

    Handle              (ID object_id, PoolType* owner_pool) : object_id_(object_id), owner_pool_(owner_pool) { }
    Handle              (const Handle& rhs) = default;
    Handle              (Handle&& rhs) = default;
    Handle&   operator= (const Handle& rhs) = default;
    Handle&   operator= (Handle&& rhs) = default;

    ID id() { return object_id_; }

    obj_type& operator* () { return owner_pool_->AccessObj(object_id_); }
    obj_type* operator->() { return owner_pool_->ObjectPtr(object_id_); }

private:
    ID object_id_;
    PoolType* owner_pool_;
};

} // namespace Engine

#endif