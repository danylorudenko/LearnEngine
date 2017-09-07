#ifndef __POOL_ALLOCATOR_INL__
#define __POOL_ALLOCATOR_INL__

#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <limits>

namespace Engine
{

template<typename T>
ObjectPool<T>::ObjectPool(std::size_t initial_capacity) :
    capacity_(0),
    pool_(nullptr)
{
    ReallocatePool(initial_capacity);
}

template<typename T>
std::size_t ObjectPool<T>::Get()
{
    const size_t free_unit_id = GetFirstFreeID();
    if (free_unit_id == std::numeric_limits<std::size_t>::max()) {
        // Double pool capacity.
        ReallocatePool(capacity_ * 2);
        return Get();
    }

    UpdateState(free_unit_id, false);

    auto object_ptr = ObjectPtr(free_unit_id);
    Construct(object_ptr);

    return free_unit_id;
}

template<typename T>
void ObjectPool<T>::Release(T* obj_ptr)
{
    std::size_t object_id = GetObjectID(obj_ptr);
    if (object_id == std::numeric_limits<std::size_t>::max()) {
        throw std::runtime_error("Object does not belong to the current pool.");
    }

    Destroy(obj_ptr);
    UpdateState(object_id, true);
}

template<typename T>
bool ObjectPool<T>::IsObjectInternal(T* object_ptr)
{
    std::ptrdiff_t to_start = object_ptr - pool_;
    return to_start >= 0;
}

template<typename T>
std::size_t ObjectPool<T>::GetObjectID(T* object_ptr)
{
    if (IsObjectInternal(object_ptr)) {
        std::ptrdiff_t to_start = object_ptr - pool_;
        return to_start;
    }
    else {
        return std::numeric_limits<std::size_t>::max();
    }
}

template<typename T>
T* ObjectPool<T>::ObjectPtr(std::size_t object_ID) {
    byte* ptr = pool_ + static_cast<std::ptrdiff_t>(object_ID + POOL_UNIT_SIZE);
    return (T*)ptr;
}

template<typename T>
T& ObjectPool<T>::AccessObj(std::size_t object_ID)
{
    return *ObjectPtr(object_ID);
}

template<typename T>
void ObjectPool<T>::ReallocatePool(std::size_t target_capacity)
{
    assert(target_capacity > capacity_);
    
    if (pool_ == nullptr) {
        pool_ = new byte[POOL_UNIT_SIZE * target_capacity];
        capacity_ = target_capacity;

        for (size_t i = 0; i < target_capacity; i++) {
            state_map_.emplace(i, true);
        }
    }
    // if pool is already allocated, alloc new and perform fast move.
    else {
        byte* new_pool = new byte[POOL_UNIT_SIZE * target_capacity];
        MovePool(pool_, new_pool, capacity_);
        delete[] pool_;
        
        pool_ = new_pool;

        size_t additional_val_count = target_capacity - capacity_;
        for (size_t i = 0; i < additional_val_count; i++) {
            state_map_.emplace(capacity_ + i, true);
        }

        capacity_ = target_capacity;
    }
}

template<typename T>
void ObjectPool<T>::MovePool(byte* source_pool, byte* destination_pool, std::size_t capacity)
{
    std::size_t iterations = capacity * POOL_UNIT_SIZE / sizeof(align_type);

    aligned_ptr source  = reinterpret_cast<aligned_ptr>(source_pool);
    aligned_ptr dest    = reinterpret_cast<aligned_ptr>(destination_pool);
    for (size_t i = 0; i < iterations; i++)
    {
        *(dest++) = *(source++);
    }
}

template<typename T>
std::size_t ObjectPool<T>::GetFirstFreeID() const
{   
    using state_value = pool_map::value_type;
    auto state_iter = 
        std::find_if(state_map_.begin(), state_map_.end(), 
        [](const state_value& value) {
            return std::get<1>(value); 
        }
    );

    if (state_iter != state_map_.end()) {
        return std::get<0>(*state_iter);
    }
    else {
        return std::numeric_limits<std::size_t>::max();
    }
}

template<typename T>
void ObjectPool<T>::UpdateState(std::size_t unit_ID, bool state)
{
    state_map_.at(unit_ID) = state;
}

} // namespace Engine

#endif