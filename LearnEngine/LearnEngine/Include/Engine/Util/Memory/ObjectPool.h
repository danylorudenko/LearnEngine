#ifndef __POOL_ALLOCATOR_H__
#define __POOL_ALLOCATOR_H__

#include <cstddef>
#include <cstdint>
#include <map>
#include <utility>

namespace Engine
{

template<typename T, typename ID_type>
class ObjectPool
{
public:
    using type = T;
    using ID = ID_type;
    using id_type = ID_type;
    using align_type = std::uint32_t;
    using aligned_ptr = align_type*;
    using byte = std::uint8_t;
    using pool_map = std::map<ID, bool>;
    
    // Each unit is aligned to the std::uint32_t for faster copying.
    static constexpr std::size_t POOL_UNIT_SIZE = sizeof(type) + (alignof(type) % sizeof(std::uint32_t));


    ObjectPool                              (std::size_t initial_capacity = 20);

    // Construct object in the pool and get pointer to it.
    template<typename... Args>
    ID                  NewObject           (Args&&... args);

    // Call destructor on object and return object to the pool.
    void                Release             (ID obj_id);

    // Check if object with in this adress belongs to this pool.
    bool                IsObjectInternal    (T* obj_ptr);

    // Get object pointer by ID.
    // This does not perform check wheather object is constructed with this ID.
    T*                  ObjectPtr           (ID object_ID);

    T&                  ObjectRef           (ID object_ID);

protected:
    // Get object ID by his adress. No check if object with this adress was constructed.
    // Performs simple check of adress belongs the the pool.
    ID                  GetObjectID         (T* object_ptr);

    // Reallocate pool with the new capacity.
    // Performs fast move of entire old pool to the new pool.
    void                ReallocatePool      (std::size_t new_capacity);
    
    // Fast pool move.
    static void         MovePool            (byte* current_pool, byte* target_pool, std::size_t capacity);

    // Find first free pool unit.
    ID                  GetFirstFreeID      () const;

    // Update state of the unit with given ID.
    void                UpdateState         (ID, bool state);

    // Placement-new by the given adress.
    template<typename... Args>
    static T*           Construct           (T* ptr, Args&&... args) { return new (ptr) T{ std::forward<Args>(args)...}; }

    // Call destructor by the given adress.
    static void         Destroy             (T* obj_ptr) { ptr->~T(); }


protected:
    std::size_t         capacity_;

    pool_map            state_map_;
    byte*               pool_;
};

} // namespace Engine

#include <Engine/Inl/ObjectPool.inl>

#endif