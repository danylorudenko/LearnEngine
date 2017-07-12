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
    
    Entity                                                      ();

    Entity                                                      (const Entity& rhs);
    Entity&                         operator=                   (const Entity& rhs);

    Entity                                                      (Entity&& rhs);
    Entity&                         operator=                   (Entity&& rhs);

    template<typename TComponent>
    std::weak_ptr<TComponent>       GetComponent                ()
    {
        for (auto component : components_) {
            if (auto casted_component = std::dynamic_pointer_cast<TComponent>(component)) {
                return casted_component;
            }
        }
    }

    void                            AddComponent                (std::shared_ptr<Component>& component);
    void                            AddComponent                (std::shared_ptr<Component>&&);
    void                            RemoveComponent             (std::weak_ptr<Component> to_remove);

protected:
    ComponentList           components_;
};

#endif