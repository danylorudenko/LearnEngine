#include <GL\glew.h>

#include <Engine\Program\Program.h>
#include <Engine\Input\InputSystem.h>
#include <Engine\RenderingSystem\RenderingSystem.h>
#include <Engine\ScriptingSystem\ScriptingSystem.h>
#include <Engine\Util\Debugging\DebugTools.h>
#include <Engine\Entity\Entity.h>
#include <Engine\World\World.h>

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
        InputSystem::Instance().ResetFrameData();
    }
}

void Program::Close()
{
    glfwSetWindowShouldClose(main_window_, true);
}