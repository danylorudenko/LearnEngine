#include "..\Include\Util\InitUtils.h"
#include "..\Include\Util\Input.h"
#include <iostream>

void key_callback(GLFWwindow* window, int key, int scan_code, int action, int mode)
{
	// If user presses ESCAPE, close the window
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

    if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        MODIFIER_OVERLOAD += 1000;
        std::cout << "W down!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    }
}