#ifndef __HANDLE_H__
#define __HANDLE_H__

#include <cstddef>

class Handle
{
public:
    Handle(void* type_handle);

    template<typename T>
    virtual T* operator->() = 0;

    template<typename T>
    virtual T* operator->() const = 0;

    virtual void DestroyObj() = 0;

private:

    template<typename HandleT>
    virtual HandleT* GetTypeHandle() const = 0;
    
};

#endif