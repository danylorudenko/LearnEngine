#ifndef __HANDLE_H__
#define __HANDLE_H__

template<typename ID_type, typename PoolType>
class Handle
{
public:
    using ID = ID_type;
    using obj_type = PoolType::type;

    Handle              (ID object_id, PoolType* owner_pool) : object_id_(object_id), owner_pool_(owner_pool) { }
    Handle              (const Handle& rhs);
    Handle              (Handle&& rhs);
    Handle&   operator= (const Handle& rhs);
    Handle&   operator= (Handle&& rhs);


    obj_type& operator* () { return owner_pool_->AccessObj(object_id_); }
    obj_type* operator->() { return owner_pool_->ObjectPtr(object_id_); }

private:
    ID object_id_;
    PoolType* owner_pool_;
};

#endif