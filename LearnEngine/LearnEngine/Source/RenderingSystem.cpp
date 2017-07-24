#include "..\Include\RenderingSystem\RenderingSystem.h"
#include "..\Include\Util\Debugging\DebugTools.h"
#include <glm\mat4x4.hpp>

#include <algorithm>

RenderingSystem::RenderingSystem(int resolution_X, int resolution_Y, std::shared_ptr<Camera> main_cam) :
    screen_width_(resolution_X), screen_height_(resolution_Y), main_camera_(main_cam)
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glEnable(GL_DEPTH_TEST);
}

void RenderingSystem::Iterate(GLFWwindow* window)
{
    Clear();

    uniform_buffer_.UpdateCameraData(
        main_camera_->GetWorldPosition(),
        main_camera_->GetViewDirection(),
        static_cast<GLfloat>(screen_width_) / static_cast<GLfloat>(screen_height_),
        DEFAULT_FOW,
        main_camera_->GetClippingPlanes()[0], main_camera_->GetClippingPlanes()[1]
    );
    uniform_buffer_.Bind();

    DrawAll(window);

    display_gl_errors();
}

void RenderingSystem::DrawAll(GLFWwindow* window)
{
    int count = static_cast<int>(rendering_list_.size());
    for (int i = 0; i < count; ++i) {
        rendering_list_[i]->BindToRender();
        glDrawArraysIndirect(GL_TRIANGLES, (GLvoid*)0);
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
        [to_remove](GLObject* candidate) { return candidate == to_remove; });
}

void RenderingSystem::frame_buffer_size_callback(GLFWwindow * window, int width, int height)
{
    RenderingSystem::Instance().SetViewport(width, height);
}
