#ifndef __INIT_UTILS_H__
#define __INIT_UTILS_H__

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "..\..\Include\Shaders\ShaderProgram.h"

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

// Global startup logic
int Start();

int InitGLFW();

// Opening GLFW Window
// Returns !0 in case of error
int OpenWindow(GLFWwindow*& window, int*& width, int*& height);

// Initializing GLEW.
// Returns !0 in case of error
int InitGLEW();

// Setting Viewport for OpenGL to draw in
void SetViewport(GLFWwindow*& window, int*& width, int*& height);

// Start checking for instruction to close the window.
// Swapping front and back buffers if there were no instructions.
// Calls glfwTerminate at the end of the loop.
void StartGameLoop(GLFWwindow*& window);

#endif