#ifndef __SINGLETONE_H__
#define __SINGLETONE_H__

#include <stdexcept>

template<typename T>
class Singletone
{
public:
    static T& Instance()
    {
        return *instance_;
    }

    static void CreateDefault()
    {
        instance_ = new T();
    }

    template<typename... Targs>
    static void Create(Targs... arg)
    {
        if (instance_ != nullptr) {
            throw std::logic_error("Logical error: singletone already has an instance. Manualy delete the previous one to create a new..");
        }
        instance_ = new T(std::forward(arg...));
    }

    static bool IsPresent()
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

#endif