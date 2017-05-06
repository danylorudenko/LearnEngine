#include "..\Include\Util\Input.h"

void key_callback(GLFWwindow* window, int key, int scan_code, int action, int mode)
{
	// If user presses ESCAPE, close the window
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}