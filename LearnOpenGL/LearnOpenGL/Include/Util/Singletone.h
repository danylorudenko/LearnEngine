#ifndef __SINGLETONE_H__
#define __SINGLETONE_H__

#include <stdexcept>

template<typename T>
class Singletone
{
public:
    Singletone()
    {
        CreateDefault();
    }

    template<typename... Targs>
    Singletone(Targs... args)
    {
        Create(std::forward(args...));
    }

    T& Instance()
    {
        return *instance_;
    }

    void CreateDefault()
    {
        instance_ = new T();
    }

    template<typename... Targs>
    void Create(Targs... arg)
    {
        if (instance_ != nullptr) {
            throw std::logic_error("Logical error: singletone already has an instance. Manualy delete the previous one to create a new..");
        }
        instance_ = new T(std::forward(arg...));
    }

    void Delete()
    {
        delete instance_;
        instance_ = nullptr;
    }

    ~Singletone()
    {
        if (instance_ != nullptr) {
            delete instance_;
        }
    }

protected:
    T* instance_;
};

#endif