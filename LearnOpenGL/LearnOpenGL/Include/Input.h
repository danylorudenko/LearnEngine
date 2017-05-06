#ifndef __INPUT_H__
#define __INPUT_H__

#include <GLFW\glfw3.h>

// Called by GLFW to handle user input
void key_callback(GLFWwindow* window, int key, int scan_code, int action, int move);

#endif