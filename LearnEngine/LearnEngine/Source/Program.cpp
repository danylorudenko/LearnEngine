#include "..\Include\Program\Program.h"
#include "..\Include\Input\InputSystem.h"
#include "..\Include\ScriptingSystem\ScriptingSystem.h"
#include "..\Include\Util\Debugging\DebugTools.h"
#include "..\Include\Entity\Entity.h"
#include "..\Include\World\World.h"

Program::Program()
{
    Initialize();
}

Program::~Program()
{
    World::Delete();
    RenderingSystem::Delete();
    glfwTerminate();
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

    World::Create();
    ScriptingSystem::Create();

    auto main_camera = std::make_shared<Camera>();
    RenderingSystem::Create(main_window_, default_resolution_X, default_resolution_Y, main_camera);
}

void Program::StartMainLoop()
{
    while (!glfwWindowShouldClose(main_window_)) {
		glfwPollEvents();

        ScriptingSystem::Instance().Iterate();
        RenderingSystem::Instance().Iterate();
    }
}

void Program::frame_buffer_size_callback(GLFWwindow * window, int width, int height)
{
    RenderingSystem::Instance().SetViewport(width, height);
}