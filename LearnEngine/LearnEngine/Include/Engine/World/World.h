#ifndef __WORLD_H__
#define __WORLD_H__

#include <Engine\Util\ControlledSingleton.h>
#include <Engine\Entity\Entity.h>

namespace Engine
{

// Main world where all actions are performed.
// Must aggregate all created Entities.
// Has Empty entity as a root.
class World : public ControlledSingleton<World>
{
public:
    World                                       ();
    World                                       (const World& rhs) = delete;
    World               operator=               (const World& rhs) = delete;
    World                                       (World&& rhs) = delete;
    World               operator=               (World&& rhs) = delete;

    // Empty root entity of the world
    Entity&             Root                    ();

    // Set new root. Old root is deleted.
    void                SetRoot                 (Entity* root);

    // Find entity in heirarchy by it's name.
    Entity*             FindEntity              (std::string& name);

    virtual             ~World                  ();

protected:
    Entity* root_;
};

} // namespace Engine

#endif
