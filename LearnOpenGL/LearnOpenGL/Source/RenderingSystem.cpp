#include "..\Include\RenderingSystem\RenderingSystem.h"

RenderingSystem::RenderingSystem(int resolution_X, int resolution_Y, std::shared_ptr<Camera> main_cam) :
    resolution_X_(resolution_X), resolution_Y_(resolution_Y), main_camera_(main_cam)
{
    glClearColor(0.3f, 0.4f, 0.9f, 1.0f);

    glEnable(GL_DEPTH_TEST);
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
