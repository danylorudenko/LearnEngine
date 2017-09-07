#ifndef __RENDERING_SYSTEM_H__
#define __RENDERING_SYSTEM_H__

#include <Engine\Entity\CameraEntity.h>
#include <Engine\Component\GLObject\GLObject.h>
#include <Engine\RenderingSystem\RenderingSystemUniformBuffer.h>
#include <Engine\Util\ControlledSingleton.h>

#include <GLFW\glfw3.h>

#include <vector>

template<typename TComponent> class ComponentFactory;

// System responsible for maintaining rendering list, 
// changing state of OpenGL, sending rendering commands.
class RenderingSystem : public ControlledSingleton<RenderingSystem>
{
public:
    friend class ComponentFactory<GLObject>;

protected:
    using RenderingListContainter                   = std::vector<GLObject*>;

public:
    RenderingSystem                                 (GLFWwindow* window,
                                                     int viewport_X, int viewport_Y, 
                                                     CameraEntity* main_cam);

    RenderingSystem                                 (const RenderingSystem& rhs) = delete;
    RenderingSystem                                 (RenderingSystem&& rhs) = delete;
    
    RenderingSystem&    operator=                   (const RenderingSystem& rhs) = delete;
    RenderingSystem&    operator=                   (RenderingSystem&& rhs) = delete;

    // Aggregator for whole iteration of the rendering system.
    void                Iterate                     ();

    // Clearing screen with color and clearing depth buffer.
    void                Clear                       ();

    // Main camera rendering.
    CameraEntity&       GetMainCamera               ();

    // Set new main camera. Only one camera is currently supported.
    void                SetMainCamera               (CameraEntity * main_cam);

protected:

    // Set viewport for rendering.
    void                SetViewport                 (int resolution_X, int resolution_Y);

    // Add new GLObject to the rendering list.
    void                AddToRenderingList          (GLObject* to_add);

    // Remove GLObject from the rendering list.
    void                RemoveFromRenderingList     (GLObject* to_remove);

    // Main rendering logic. Setting states and drawing.
    void                DrawAll                     ();

    // System callback for change of the buffer size.
    static void         frame_buffer_size_callback  (GLFWwindow* window, int width, int height);


protected:
    GLFWwindow*                             context_window_;

    int                                     screen_width_;
    int                                     screen_height_;

    CameraEntity*                           main_camera_;
    RenderingListContainter                 rendering_list_;

    RenderingSystemUniformBuffer            uniform_buffer_;
};

#endif