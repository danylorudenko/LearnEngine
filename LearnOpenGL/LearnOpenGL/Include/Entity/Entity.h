#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <list>
#include <type_traits>
#include <utility>

#include "..\Component\Component.h"

class Entity
{
    using ComponentList = std::list<Component>;
public:
    


    /*
        NOTE: Template does compile-time check if passed parameter is defived from Component.
        Member-function adds new component of type TComponent with default values.
        Sets component's owner via Attorney-Client idiom.
    */
    template<
        typename TComponent,
        typename = typename std::enable_if
                            <
                                std::is_base_of
                                <
                                    Component,
                                    typename std::decay<TComponent>::type
                                >::value
                            >::type
    >
    void                    AddComponent()
    {
        TComponent temp(this);
        ComponentOwnerAttorney::SetComponentOwner(temp, this);
        components_.push_back(std::move(temp));
    }

protected:
    ComponentList           components_;
};

#endif