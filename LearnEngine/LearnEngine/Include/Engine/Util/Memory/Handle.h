#ifndef __HANDLE_H__
#define __HANDLE_H__

#include <cstddef>

class Handle
{
public:
    virtual void* operator->() = 0;
    virtual void* operator->() const = 0;

    virtual void DestroyObj() = 0;
};

#endif