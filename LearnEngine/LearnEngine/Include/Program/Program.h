#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "..\RenderingSystem\RenderingSystem.h"
#include "..\Util\InitUtils.h"

// The highest facade for engine launching.
class Program : public Singletone<Program>
{
public:
    static constexpr unsigned int           DEFAULT_RESOLUTION_X = 800;
    static constexpr unsigned int           DEFAULT_RESOLUTION_Y = 600;

    Program                         ();
    Program                         (const Program& rhs) = delete;
    Program&        operator=       (const Program& rhs) = delete;
    Program                         (Program&& rhs) = delete;
    Program&        operator=       (Program&& rhs) = delete;

    ~Program                        ();

    // Start main engine loop.
    // Waiting glfwWindowShouldClose message to exit the loop.
    void            StartMainLoop   ();

    // Send ShouldClose message to glfw.
    void            Close           ();

protected:
    // Engine initialization logic.
    // Calls the startup of the main engine loop.
    void            Initialize      ();

    // Custom actions to be executed after initialization and before the main loop.
    void            StartupLogic    ();

protected:
    GLFWwindow* main_window_;
};

#endif