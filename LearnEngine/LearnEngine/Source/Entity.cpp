#include <Engine\Entity\Entity.h>
#include <Engine\World\World.h>
#include <Engine\Component\ComponentFactory.h>

namespace Engine
{

Entity* Entity::CreateEntity()
{
    Entity* new_entity = new Entity(&World::Instance().Root());
    return new_entity;
}

Entity * Entity::CreateRootEnitity()
{
    return new Entity(nullptr);
}

Entity* Entity::FindEntity(std::string& name)
{
    if (name_ == name) {
        return this;
    }

    if (!children_.empty()) {
        std::for_each(children_.begin(), children_.end(),
            [&name, this](HierarchyMember<Entity>* candidate) {
            return dynamic_cast<Entity*>(this->FindEntity(name));
        });
    }

    return nullptr;
}

std::string & Entity::Name()
{
    return name_;
}

const std::string & Entity::Name() const
{
    return name_;
}

GLTransform & Entity::Transform()
{
    return *transform_;
}

const GLTransform & Entity::Transform() const
{
    return *transform_;
}

Entity::Entity(Entity* parent) :
    HierarchyMember<Entity>(parent),
    transform_(new GLTransform()),
    name_("new_entity")
{

}

Entity::~Entity()
{
    RemoveAllComponents();
}

void Entity::RemoveAllComponents()
{
    while (!components_.empty()) {
        Component* to_remove = *components_.begin();
        to_remove->GetDestructionFunc()(to_remove);
        components_.pop_front();
    }
}

} // namespace Engine