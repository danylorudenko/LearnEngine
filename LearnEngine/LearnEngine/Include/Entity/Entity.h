#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <list>
#include <type_traits>
#include <utility>
#include <memory>
#include <typeinfo>
#include <algorithm>

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

    virtual ~Entity                                             ();

    // Gets reference to the first component in the list of the template type.
    template<typename TComponent>
    std::weak_ptr<TComponent>       GetComponent                ()
    {
        for (auto component : components_) {
            if (auto casted_component = std::dynamic_pointer_cast<TComponent>(component)) {
                return casted_component;
            }
        }
    }

    // Adds component to the internal list and sets its owner to self.
    // Performs registration of the component in the contolling system, if needed.
    void                            AddComponent                (std::shared_ptr<Component>& component);

    // Removes pointer to the component and unregisters component from engines subsystems, if needed.
    // Removes owner pointer for the component.
    void                            RemoveComponent             (std::weak_ptr<Component> to_remove);

    // Unregisters all components registered by this entity.
    // Clears pointer list to the components.
    void                            RemoveAllComponents         ();

protected:
    ComponentList           components_;
};

#endif