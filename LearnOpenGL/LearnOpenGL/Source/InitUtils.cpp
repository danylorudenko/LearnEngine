#include "..\Include\RenderingSystem\GLObject\GLTestCube.h"
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

	auto shader_program = std::make_shared<ShaderProgram>("Shaders\\vertex_shader.vglsl", "Shaders\\fragment_shader.fglsl");

	//=====================================

    const int value_count = 180;

    std::shared_ptr<VertexData> vertices = std::make_shared<VertexData>(new GLfloat[value_count] {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    }, value_count);

    GLTestCube cube(vertices, shader_program);

	Texture2DController texture("Resources\\container.jpg", "Resources\\awesomeface.png");


	//=====================================

    //GLint64 startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		// Clearing buffer, with previously specified color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// RENDERING HERE
		glActiveTexture(GL_TEXTURE0);
		texture.Bind1();
        shader_program->SetIntUniform("myTexture1", 0);

		glActiveTexture(GL_TEXTURE1);
		texture.Bind2();
        shader_program->SetIntUniform("myTexture2", 1);

		shader_program->Use();

        cube.BindToRender();
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		// END OF RENDERING

		glfwSwapBuffers(window);
	}

	glfwTerminate();
}