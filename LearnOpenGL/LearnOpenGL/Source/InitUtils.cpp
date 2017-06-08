#include "..\Include\Util\InitUtils.h"
#include "..\Include\Util\Input.h"
#include "..\Include\Texture\Texture2DController.h"

#include <chrono>
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
		// Positions          // Colors           // Texture Coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Top Right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Bottom Right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom Left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Top Left 
	};

	GLuint indicies[] = {
		0, 1, 2,
		2, 3, 0
	};



	GLuint VBO;
	glGenBuffers(1, &VBO);

	GLuint EBO;
	glGenBuffers(1, &EBO);

	GLuint VAO;
	glGenVertexArrays(1, &VAO);


	// Binding Vertex Array object to store all preferences below
	glBindVertexArray(VAO);

	// Binding to the buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Loading data to the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

	// Some hard shit with vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// Unbinding Vertex Array Object
	glBindVertexArray(0);


	Texture2DController texture("Resources\\container.jpg", "Resources\\awesomeface.png");


	//=====================================

	GLint texure_1_uniform = glGetUniformLocation(shader_program.GetProgram(), "myTexture1");
	GLint texure_2_uniform = glGetUniformLocation(shader_program.GetProgram(), "myTexture2");

    GLint64 startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		// Clearing buffer, with previously specified color
		glClear(GL_COLOR_BUFFER_BIT);

		// RENDERING HERE
		glActiveTexture(GL_TEXTURE0);
		texture.Bind1();
		glUniform1i(texure_1_uniform, 0);

		glActiveTexture(GL_TEXTURE1);
		texture.Bind2();
		glUniform1i(texure_2_uniform, 1);

        GLint64 timePassed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - startTime;
        GLfloat colorMultiplier = static_cast<GLfloat>(timePassed) / 100;
        std::cout << colorMultiplier + MODIFIER_OVERLOAD << std::endl;
        shader_program.SetFloatUniform("colorMultiplier", colorMultiplier + MODIFIER_OVERLOAD);
		shader_program.Use();

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// END OF RENDERING

		glfwSwapBuffers(window);
	}

	glfwTerminate();
}