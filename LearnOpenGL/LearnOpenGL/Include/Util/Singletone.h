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

    template<typename... Targs>
    static void Create(Targs&&... arg)
    {
        if (instance_ != nullptr) {
            throw std::logic_error("Logical error: singletone already has an instance. Manualy delete the previous one to create a new..");
        }
        instance_ = new T(std::forward<Targs>(arg)...);
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
T* Singletone<T>::instance_ = nullptr;

#endif