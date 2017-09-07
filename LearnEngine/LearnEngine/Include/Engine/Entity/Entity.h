#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <list>
#include <utility>
#include <memory>
#include <algorithm>
#include <string>

#include <Engine\Util\HierarchyMember.h>
#include <Engine\Util\GLTransformation\GLTransform.h>
#include <Engine\Component\Component.h>

namespace Engine
{

// Main structural unit in the World.
// Can be identified only by name. Default name is "new_entity"
// Has a position, can contain components that describe it's behaviour.
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

    virtual                         ~Entity                     ();

    // Create empty entity and add it to the world.
    static Entity*                  CreateEntity                ();

    // [FOR WORLD USE ONLY] Create root entity.
    static Entity*                  CreateRootEnitity           ();

    // Find child entity in the hierarchy by the name.
    Entity*                         FindEntity                  (std::string& name);

    std::string&                    Name                        ();
    const std::string&              Name                        () const;

    GLTransform&                    Transform                   ();
    const GLTransform&              Transform                   () const;


    // Gets reference to the first component in the list of the template type.
    template<typename TComponent>
    TComponent*                     GetComponent                ();

    // Adds component to the internal list and sets its owner to self.
    // Performs registration of the component in the contolling system, if needed.
    template<typename TComponent>
    TComponent*                     AddComponent                ();

    // Removes pointer to the component and unregisters component from engines subsystems, if needed.
    // Removes owner pointer for the component.
    template<typename TComponent>
	void                            RemoveComponent				(TComponent* to_remove);

    // Unregisters all components registered by this entity.
    // Clears pointer list to the components.
    void                            RemoveAllComponents         ();

protected:
    std::unique_ptr<GLTransform>    transform_;

    std::string                     name_;
    ComponentList                   components_;
};

} // namespace Engine

#include "Engine\Inl\Entity.inl"

#endif