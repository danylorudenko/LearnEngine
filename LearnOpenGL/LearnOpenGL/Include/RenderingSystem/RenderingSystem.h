#ifndef __RENDERING_SYSTEM_H__
#define __RENDERING_SYSTEM_H__

#include "Camera.h"
#include "GLObject\GLObject.h"
#include "..\Util\Singletone.h"

#include <list>

class RenderingSystem : public Singletone<RenderingSystem>
{
public:
    RenderingSystem                         (int viewport_X, int viewport_Y,
                                             std::shared_ptr<Camera> main_cam);

    void                Iterate             ();
    void                DrawAll             ();
    void                Clear               ();

    void                SetMainCamera       (std::shared_ptr<Camera> main_cam);
    void                SetViewport         (int resolution_X, int resolution_Y);
    void                AddToDrawList       (std::shared_ptr<GLObject> new_object);
    void                RemoveFromDrawList  (std::shared_ptr<GLObject> to_remove);

protected:
    int                                     resolution_X_;
    int                                     resolution_Y_;

    std::shared_ptr<Camera>                 main_camera_;
    std::list<std::weak_ptr<GLObject>>      gl_objects_;
};

#endif