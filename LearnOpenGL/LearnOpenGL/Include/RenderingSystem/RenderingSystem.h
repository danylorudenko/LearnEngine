#ifndef __RENDERING_SYSTEM_H__
#define __RENDERING_SYSTEM_H__

#include "Camera.h"
#include "GLObject\GLObject.h"
#include "..\Util\Singletone.h"

#include <list>

class RenderingSystem : public Singletone<RenderingSystem>
{
public:
    void                DrawAll             ();

protected:

    std::weak_ptr<Camera> main_camera_;
    std::list<std::weak_ptr<GLObject>>      gl_objects_;
};

#endif