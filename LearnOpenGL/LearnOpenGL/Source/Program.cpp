#include "..\Include\Program.h"

Program::Program()
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
    
    RenderingSystem::Instance().Create(default_resolution_X, default_resolution_Y);

}

void Program::Initialize()
{

}