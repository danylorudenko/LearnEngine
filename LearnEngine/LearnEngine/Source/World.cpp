#include "..\Include\World\World.h"

World::World() :
    root_(Entity::CreateRootEnitity())
{
    
}

void World::AddToRoot(Entity* entity)
{
    root_->AddChildToListWithIndex(entity);
}

void World::SetRoot(Entity* root)
{
    delete root_;
    root_ = root;
}

Entity* World::FindEntity(std::string& name)
{
    return root_->FindEntity(name);
}

World::~World()
{
    delete root_;
}
