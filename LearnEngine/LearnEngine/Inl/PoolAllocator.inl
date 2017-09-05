#ifndef __POOL_ALLOCATOR_INL__
#define __POOL_ALLOCATOR_INL__

#include <cstdlib>
#include <cassert>

template<typename T>
ObjectPool<T>::ObjectPool(std::size_t initial_capacity) :
    capacity_(0),
    count_(0),
    next_free_unit_id_(0),
    pool_(nullptr)
{
    ReinitializePool(initial_capacity);
}

template<typename T>
T* ObjectPool<T>::GetObjectPtr(std::size_t object_ID) {
    return (pool_ + static_cast<std::ptrdiff_t>(object_ID + POOL_UNIT_SIZE));
}

template<typename T>
void ObjectPool<T>::ReinitializePool(std::size_t target_capacity)
{
    assert(target_capacity > capacity_);
    
    if (pool_ == nullptr) {
        pool_ = std::malloc(POOL_UNIT_SIZE * target_capacity);
        capacity_ = target_capacity;

        for (size_t i = 0; i < initial_capacity; i++) {
            state_map_.emplace(i, false);
        }
    }
    // if pool is already allocated, alloc new and perform fast move.
    else {
        byte new_pool = std::malloc(target_capacity);
        MovePool(pool_, new_pool, capacity_);

        std::free(pool_);
        pool_ = new_pool;

        size_t additional_val_count = target_capacity - capacity_;
        for (size_t i = 0; i < additional_cal_count; i++) {
            state_map_.emplace(capacity_ + additional_val_count);
        }

        capacity_ = target_capacity;
    }
}

template<typename T>
void ObjectPool<T>::MovePool(T* source_pool, T* destination_pool, std::size_t count)
{
    std::size_t iterations = count * POOL_UNIT_SIZE;

    aligned_ptr source  = reinterpret_cast<aligned_ptr>(source_pool);
    aligned_ptr dest    = reinterpret_cast<aligned_ptr>(destination_pool);
    for (size_t i = 0; i < iterations; i++)
    {
        *(source++) = *(dest++);
    }
}

template<typename T>
void ObjectPool<T>::GetFirstFreeID() const
{
    auto first_free_predicate = [](const state_map_::mapped_type& lhs, const state_map_::mapped_type& rhs) {
        return true;
    }; IN PROGRESS
}

template<typename T>
void ObjectPool<T>::UpdateState(std::size_t unit_ID, bool state)
{
    state_map_.at(unit_ID) = state;
}

#endif