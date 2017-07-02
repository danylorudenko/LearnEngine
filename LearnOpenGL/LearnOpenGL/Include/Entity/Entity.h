#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <list>
#include <type_traits>
#include <utility>
#include <memory>
#include <typeinfo>

#include "..\Component\Component.h"

class Entity
{
    using ComponentList = std::list<std::shared_ptr<Component>>;
public:
    
    Entity                                          ();

    Entity                                          (const Entity& rhs);
    Entity              operator=                   (const Entity& rhs);

    Entity                                          (Entity&& rhs);
    Entity              operator=                   (Entity&& rhs);

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
    void AddComponent()
    {
        components_.push_back(std::move(std::make_shared<TComponent>(this));
    }

    /*
        NOTE: Template does compile-time check if passed parameter is defived from Component.
        Checks if there are components with same memory location as to_remove, deletes them, if there are.
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
    void RemoveComponent(std::weak_ptr<TComponent> to_remove)
    {
        components_.remove_if([](std::shared_ptr<Component> component) { return component.get() == to_remove.lock().get()); });
    }


    /*
        NOTE: Template does compile-time check if passed parameter is defived from Component.
        Returns component of the specified type.
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
    std::weak_ptr<TComponent> GetComponent()
    {
        for (auto component : components_) {
            if (auto casted_component = std::dynamic_pointer_cast<TComponent>(component) {
                return casted_component;
            }
        }
    }

protected:
    ComponentList           components_;
};

#endif