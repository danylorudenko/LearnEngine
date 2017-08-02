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
    ScriptingSystem::Delete();
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
    if (OpenWindow_SetContext(main_window_, DEFAULT_RESOLUTION_X, DEFAULT_RESOLUTION_Y) != 0) {
        throw std::runtime_error("Error opening window.");
    }

    // ================

    if (InitGLEW() != 0) {
        throw std::runtime_error("Error initializing GLEW.");
    }

    World::Create();
    ScriptingSystem::Create();
    InputSystem::Create(main_window_);

    RenderingSystem::Create(
        main_window_, 
        DEFAULT_RESOLUTION_X, 
        DEFAULT_RESOLUTION_Y, 
        CameraEntity::CreateCamera()
    );
}

void Program::StartMainLoop()
{
    StartupLogic();
    
    while (!glfwWindowShouldClose(main_window_)) {
		glfwPollEvents();

        ScriptingSystem::Instance().Iterate();
        RenderingSystem::Instance().Iterate();
    }
}

void Program::Close()
{
    glfwSetWindowShouldClose(main_window_, true);
}