#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <list>
#include <utility>
#include <memory>
#include <algorithm>
#include <string>

#include "..\Util\HierarchyMember.h"
#include "..\Component\Component.h"
#include "..\Component\GLObject\GLTransformation\GLTransform.h"

class Entity : public HierarchyMember<Entity>
{
protected:
    Entity                                                      (Entity* parent);

public:
    using ComponentList = std::list<Component*>;

    Entity                                                      (const Entity& rhs) = delete;
    Entity&                         operator=                   (const Entity& rhs) = delete;

    Entity                                                      (Entity&& rhs) = delete;
    Entity&                         operator=                   (Entity&& rhs) = delete;

    virtual ~Entity                                             ();


    static Entity*                  CreateEntity                ();
    static Entity*                  CreateRootEnitity           ();

    Entity*                         FindEntity                  (std::string& name);

    std::string&                    Name                        ();
    GLTransform&                    Transform                   ();


    // Gets reference to the first component in the list of the template type.
    template<typename TComponent>
    TComponent*                     GetComponent                ()
    {
        for (auto component : components_) {
            if (auto casted_component = dynamic_cast<TComponent*>(component)) {
                return casted_component;
            }
        }

        return nullptr;
    }

    // Adds component to the internal list and sets its owner to self.
    // Performs registration of the component in the contolling system, if needed.
    void                            AddComponent                (Component* component);

    // Removes pointer to the component and unregisters component from engines subsystems, if needed.
    // Removes owner pointer for the component.
    void                            RemoveComponent             (Component* to_remove);

    // Unregisters all components registered by this entity.
    // Clears pointer list to the components.
    void                            RemoveAllComponents         ();

protected:
    std::unique_ptr<GLTransform>    transform_;

    std::string                     name_;
    ComponentList                   components_;
};

#endif