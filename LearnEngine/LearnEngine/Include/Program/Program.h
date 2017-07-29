#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "..\RenderingSystem\RenderingSystem.h"
#include "..\Util\InitUtils.h"

class Program : public Singletone<Program>
{
public:
    static constexpr unsigned int           default_resolution_X = 800;
    static constexpr unsigned int           default_resolution_Y = 600;


    Program                         ();
    Program                         (const Program& rhs) = delete;
    Program&        operator=       (const Program& rhs) = delete;
    Program                         (Program&& rhs) = delete;
    Program&        operator=       (Program&& rhs) = delete;

    ~Program                        ();


    void            Initialize      ();
    void            StartMainLoop   ();


    void            frame_buffer_size_callback(GLFWwindow* window, int width, int height);

protected:
    void            StartupLogic    ();

protected:
    GLFWwindow* main_window_;
};

#endif