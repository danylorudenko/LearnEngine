#ifndef __CONTROLLED_SINGLETON_H__
#define __CONTROLLED_SINGLETON_H__

// Singleton with controlled existance of the instance.
template<typename T>
class ControlledSingleton
{
public:
    // Get reference to the internal instance.
    // UB if instance was not created.
    static T& Instance();

    // Forward arguments to the instance constructor and create instance.
    template<typename... TArgs>
    static void Create(TArgs&&... args);

    // Is instance created?
    static bool IsCreated();

    // Free instance memory and set instance ptr to nullptr.
    static void Delete();

protected:
    static T* instance_;
};

#include "..\..\Inl\ControlledSingleton.inl"

#endif