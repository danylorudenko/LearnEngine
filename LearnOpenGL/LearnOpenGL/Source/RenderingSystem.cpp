#include "..\Include\RenderingSystem\RenderingSystem.h"

RenderingSystem::RenderingSystem(int resolution_X, int resolution_Y, std::shared_ptr<Camera> main_cam) :
    resolution_X_(resolution_X), resolution_Y_(resolution_Y), main_camera_(main_cam)
{
    glClearColor(0.3f, 0.4f, 0.9f, 1.0f);

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
        glObjectPtr->BindToRender();
        glObjectPtr->DrawCall(main_camera_, resolution_X_, resolution_Y_);
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
    resolution_X_ = resolution_X;
    resolution_Y_ = resolution_Y;

    glViewport(0, 0, resolution_X_, resolution_Y_);
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
