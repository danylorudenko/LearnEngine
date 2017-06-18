#include "..\Include\Program.h"
#include <memory>

Program::Program()
{
    Initialize();
}

void Program::Initialize()
{
    if (InitGLFW() != 0) {
        throw std::runtime_error("Error initializing GLFW");
    }

    // ================

    main_window_ = nullptr;
    if (OpenWindow_SetContext(main_window_, default_resolution_X, default_resolution_Y) != 0) {
        throw std::runtime_error("Error opening window.");
    }

    // ================

    if (InitGLEW() != 0) {
        throw std::runtime_error("Error initializing GLEW.");
    }

    // ================

    auto main_camera = std::make_shared<Camera>(default_resolution_X, default_resolution_Y);
    RenderingSystem::Instance().Create(default_resolution_X, default_resolution_Y, main_camera);
}

void Program::StartMainLoop()
{
    while (glfwWindowShouldClose(main_window_)) {
        RenderingSystem::Instance().Iterate();
    }
}