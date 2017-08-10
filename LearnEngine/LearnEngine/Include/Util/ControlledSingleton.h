#ifndef __SINGLETONE_H__
#define __SINGLETONE_H__

#include <stdexcept>

template<typename T>
class ControlledSingleton
{
public:
    static T& Instance()
    {
        return *instance_;
    }

    template<typename... TArgs>
    static void Create(TArgs&&... arg)
    {
        if (instance_ != nullptr) {
            throw std::logic_error("Logical error: singletone already has an instance. Manualy delete the previous one to create a new..");
        }
        instance_ = T::ConstructionAttorney::ConstructInstance(std::forward<TArgs>(arg)...);
    }

    static bool IsCreated()
    {
        return instance_ != nullptr;
    }

    static void Delete()
    {
        delete instance_;
        instance_ = nullptr;
    }

protected:
    static T* instance_;
};

template<typename T>
T* ControlledSingleton<T>::instance_ = nullptr;

#endif