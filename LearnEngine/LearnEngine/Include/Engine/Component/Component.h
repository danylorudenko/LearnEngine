#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <utility>

namespace Engine
{

class Entity;

// Base abtract class for all components which can be attached to the 
class Component
{
public:
    Component                               (Entity* owner);
    Component                               (const Component& rhs) = delete;
    Component&          operator=           (const Component& rhs) = delete;
    Component                               (Component&& rhs) = delete;
    Component&          operator=           (Component&& rhs) = delete;

    virtual ~Component                      ();

    Entity&             GetOwner            ();

protected:
    Entity* owner_;
};

} // namespace Engine

#endif