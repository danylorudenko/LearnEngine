#include "..\Include\Entity\Entity.h"
#include "..\Include\Component\ComponentRegistrationAttorney.h"

Entity::Entity()
{

}

Entity::Entity(const Entity & rhs) : components_(rhs.components_)
{

}

Entity::Entity(Entity&& rhs) : components_(std::move(rhs.components_))
{

}

Entity& Entity::operator=(const Entity& rhs)
{
    components_ = rhs.components_;
}

Entity& Entity::operator=(Entity&& rhs)
{
    components_ = std::move(rhs.components_);
}

Entity::~Entity()
{
    RemoveAllComponents();
}

void Entity::AddComponent(std::shared_ptr<Component>& component)
{
    components_.push_back(component);
    ComponentRegistrationAttorney::SetComponentOwner(component, this);
    ComponentRegistrationAttorney::RegisterInSystem(component);
}

void Entity::RemoveComponent(std::weak_ptr<Component> component)
{
    // If locked std::shared_ptr is not nullptr..
    if (auto to_remove = component.lock()) {
        ComponentRegistrationAttorney::UnregisterFromSystem(to_remove);
        
        components_.remove_if(
            [=](std::shared_ptr<Component>& candidate) {
            return to_remove == candidate;
        });
    }
}

void Entity::RemoveAllComponents()
{
    for (auto component : components_) {
        ComponentRegistrationAttorney::UnregisterFromSystem(component);
        ComponentRegistrationAttorney::SetComponentOwner(component, nullptr);
    }

    components_.clear();
}
