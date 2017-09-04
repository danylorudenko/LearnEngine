#ifndef __INIT_UTILS_H__
#define __INIT_UTILS_H__

#include <gl\glew.h>
#include <GLFW\glfw3.h>

// Initializing GLFW, setting basic preferences.
// Returns !0 in case of error.
int InitGLFW();

// Opening GLFW Window
// Returns !0 in case of error
int OpenWindow_SetContext(GLFWwindow*& window, int width, int height);

// Initializing GLEW.
// Returns !0 in case of error
int InitGLEW();

#endif