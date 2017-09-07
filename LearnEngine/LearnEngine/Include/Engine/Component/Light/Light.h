#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <Engine\Component\Component.h>

namespace Engine
{

class Light : public Component
{
public:
    Light                                   (Entity* owner);
    Light                                   (const Light& rhs) = delete;
    Light                                   (Light&& rhs) = delete;
    Light&              operator=           (const Light& rhs) = delete;
    Light&              operator=           (Light&& rhs) = delete;
};

} // namespace Engine

#endif