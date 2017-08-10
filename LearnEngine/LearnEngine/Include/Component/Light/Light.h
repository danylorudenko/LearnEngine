#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "..\Component.h"

class Light : public Component
{
public:

    Light                                   ();
    Light                                   (const Light& rhs) = delete;
    Light                                   (Light&& rhs) = delete;
    Light&              operator=           (const Light& rhs) = delete;
    Light&              operator=           (Light&& rhs) = delete;
};

#endif