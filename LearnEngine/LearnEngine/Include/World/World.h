#ifndef __WORLD_H__
#define __WORLD_H__

#include "..\Util\Singletone.h"
#include "..\Entity\Entity.h"

class World : public Singletone<World>
{
public:
    World                                       ();
    World                                       (const World& rhs) = delete;
    World               operator=               (const World& rhs) = delete;
    World                                       (World&& rhs) = delete;
    World               operator=               (World&& rhs) = delete;


    void                AddToRoot               (Entity* entity);
    void                SetRoot                 (Entity* root);

    Entity*             FindEntity              (std::string& name);

    virtual ~World                              ();

protected:
    Entity* root_;
};

#endif
