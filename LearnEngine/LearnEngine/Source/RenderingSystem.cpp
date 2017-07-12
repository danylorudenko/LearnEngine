#include "..\Include\RenderingSystem\RenderingSystem.h"
#include "..\Include\Util\Debugging\DebugTools.h"
#include <glm\mat4x4.hpp>

RenderingSystem::RenderingSystem(int resolution_X, int resolution_Y, std::shared_ptr<Camera> main_cam) :
    screen_width_(resolution_X), screen_height_(resolution_Y), main_camera_(main_cam)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
}

void RenderingSystem::Iterate(GLFWwindow* window)
{
    Clear();
    DrawAll(window);
}

void RenderingSystem::DrawAll(GLFWwindow* window)
{
    for (auto glObjectPtr : gl_objects_) {
        glObjectPtr->BindToRender(main_camera_->GetViewMatrix(), 
                                  main_camera_->GetPerspectiveMatrix(screen_width_, screen_height_));

        glObjectPtr->DrawCall();
    }

    glfwSwapBuffers(window);
}

void RenderingSystem::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderingSystem::SetMainCamera(std::shared_ptr<Camera> main_cam)
{
    main_camera_ = main_cam;
}

void RenderingSystem::SetViewport(int resolution_X, int resolution_Y)
{
    screen_width_ = resolution_X;
    screen_height_ = resolution_Y;

    glViewport(0, 0, screen_width_, screen_width_);
}

void RenderingSystem::AddToDrawList(std::shared_ptr<GLObject> new_object)
{
    gl_objects_.push_back(new_object);
}

void RenderingSystem::RemoveFromDrawList(std::shared_ptr<GLObject> to_remove)
{
    gl_objects_.remove(to_remove);
}

void RenderingSystem::frame_buffer_size_callback(GLFWwindow * window, int width, int height)
{
    RenderingSystem::Instance().SetViewport(width, height);
}
