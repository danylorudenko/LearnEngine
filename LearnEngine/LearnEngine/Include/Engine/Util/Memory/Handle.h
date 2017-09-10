#ifndef __HANDLE_H__
#define __HANDLE_H__

#include <cstddef>

namespace Engine
{

class Handle
{
public:
    virtual void* Ptr() = 0;
    virtual void const* Ptr() const = 0;

    template<typename HandleT>
    HandleT* TypeHandle() { return dynamic_cast<HandleT*>(this); }

    virtual void DestroyObj() = 0;
};

template<typename T>
T* Ptr(Handle handle) { return dynamic_cast<T*>(handle.Ptr()); }

template<typename T>
T& Ref(Handle handle) { return *(Ptr<T>(handle)); }

} // namespace Engine

#endif