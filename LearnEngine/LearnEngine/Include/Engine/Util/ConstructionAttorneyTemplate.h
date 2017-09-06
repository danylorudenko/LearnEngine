#ifndef __CONSTRUCTION_ATTORNEY_H__
#define __CONSTRUCTION_ATTORNEY_H__

#include <Engine\Util\ControlledSingleton.h>

template<typename T>
class SingletonConstructionAttorneyTemplate
{
private:
    template<typename... TArgs>
    static T* ConstructInstance(TArgs&&... args)
    {
        return new T(args...);
    }

    friend class ControlledSingleton<T>;
};

#endif