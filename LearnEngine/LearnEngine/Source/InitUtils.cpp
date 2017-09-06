#include <Engine\Util\InitUtils.h>
#include <Engine\Input\InputSystem.h>
#include <Engine\Shaders\ShaderProgram.h>

#include <iostream>
#include <stdexcept>

int InitGLFW()
{
	if (glfwInit() == GLFW_FALSE)
	{
		std::cerr << "[GLFW] Initialization error.\n";
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	return 0;
}

int OpenWindow_SetContext(GLFWwindow*& window, int width, int height)
{
	window = glfwCreateWindow(width, height, "Hello, OpenGL", nullptr, nullptr);
	if (window == nullptr) {
		std::cerr << "[GLFW] Error creating window.\n";
		return -1;
	}

	glfwMakeContextCurrent(window);

	return 0;
}

int InitGLEW()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "[GLEW] Initialization error.\n";
		return -1;
	}
	return 0;
}