#include "..\Include\Util\InitUtils.h"
#include "..\Include\Util\Input.h"

#include <iostream>

int Start()
{
	int* width = nullptr;
	int* height = nullptr;
	GLFWwindow* window = nullptr;

	if (InitGLFW() != 0) {
		system("pause");
		return -1;
	}
	if (OpenWindow(window, width, height) != 0) {
		system("pause");
		return -1;
	}
	if (InitGLEW() != 0) {
		system("pause");
		return -1;
	}

	StartGameLoop(window);

	return 0;
}

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
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	return 0;
}

int OpenWindow(GLFWwindow*& window, int*& width, int*& height)
{
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello, OpenGL", nullptr, nullptr);
	if (window == nullptr) {
		std::cerr << "[GLFW] Error creating window.\n";
		return -1;
	}

	glfwGetFramebufferSize(window, width, height);
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

void SetViewport(GLFWwindow*& window, int*& width, int*& height)
{
	glfwGetFramebufferSize(window, width, height);

	glViewport(0, 0, *width, *height);
}

void StartGameLoop(GLFWwindow*& window)
{
	// Setting key callback function
	glfwSetKeyCallback(window, key_callback);

	// Setting color to clear the buffer
	glClearColor(0.3f, 0.4f, 0.9f, 1.0f);

	ShaderProgram shader_program("Shaders\\vertex_shader.vglsl", "Shaders\\fragment_shader.fglsl");

	//=====================================


	GLfloat vertices[] = {
		// Positions         // Colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // Bottom Right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // Bottom Left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // Top 
	};

	GLuint VBO;
	glGenBuffers(1, &VBO);

	GLuint VAO;
	glGenVertexArrays(1, &VAO);


	// Binding Vertex Array object to store all preferences below
	glBindVertexArray(VAO);

	// Binding to the buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Loading data to the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Some hard shit with vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Unbinding Vertex Array Object
	glBindVertexArray(0);



	//=====================================


	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		// Clearing buffer, with previously specified color
		glClear(GL_COLOR_BUFFER_BIT);

		// RENDERING HERE

		shader_program.Use();

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		// END OF RENDERING

		glfwSwapBuffers(window);
	}

	glfwTerminate();
}