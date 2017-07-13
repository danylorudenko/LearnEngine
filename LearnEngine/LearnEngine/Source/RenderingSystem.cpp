#include "..\Include\RenderingSystem\RenderingSystem.h"
#include "..\Include\Util\Debugging\DebugTools.h"
#include <glm\mat4x4.hpp>

#include <algorithm>

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
    int count = rendering_list_.size();

    auto view_matrix = main_camera_->GetViewMatrix();
    auto perspective_matrix = main_camera_->GetPerspectiveMatrix(screen_width_, screen_height_);
    for (int i = 0; i < count; ++i) {
        rendering_list_[i]->BindToRender(view_matrix, perspective_matrix);
        
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

void RenderingSystem::AddToDrawList(GLObject* to_add)
{
    rendering_list_.push_back(to_add);
}

void RenderingSystem::RemoveFromDrawList(GLObject* to_remove)
{
    std::remove_if(rendering_list_.begin(), rendering_list_.end(),
        [to_remove](GLObject* candidate) { candidate == to_remove; });
}

void RenderingSystem::frame_buffer_size_callback(GLFWwindow * window, int width, int height)
{
    RenderingSystem::Instance().SetViewport(width, height);
}
