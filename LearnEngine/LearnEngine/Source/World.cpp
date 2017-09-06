#include <Engine\World\World.h>

World::World() :
    root_(Entity::CreateRootEnitity())
{
    
}

Entity& World::Root()
{
    return *root_;
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
