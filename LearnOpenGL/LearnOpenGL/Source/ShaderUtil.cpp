#include "..\Include\Shaders\ShaderUtil.h"

#include <fstream>
#include <stdexcept>
#include <iostream>

GLchar* ReadStringFromFile(const std::string& file_name)
{
	std::ifstream in_stream(file_name, std::ios_base::in);

	if (!in_stream.is_open()) {
		throw std::invalid_argument("No such file or directory.");
	}

	in_stream.seekg(0, std::ios_base::end);
	int file_length = static_cast<int>(in_stream.tellg());
	in_stream.seekg(0, std::ios_base::beg);

	GLchar* file_content = new GLchar[file_length + 1];

	int read_position = 0;
	while (in_stream.good()) {
		file_content[read_position] = in_stream.get();
		++read_position;
	}

	file_content[read_position] = '\0';

	in_stream.close();

	return file_content;
}

GLuint CompileVertexShader()
{
	GLchar* vertex_string = ReadStringFromFile("Shaders\\vertex_shader.vshader");
	GLuint vertex_shader = 0;
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertex_shader, 1, &vertex_string, NULL);
	glCompileShader(vertex_shader);

	delete[] vertex_string;

	GLint success;
	GLchar infolog[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertex_shader, sizeof(infolog), NULL, infolog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << std::endl;
	}

	return vertex_shader;
}

GLuint CompileFragmentShader()
{
	GLchar* fragment_string = ReadStringFromFile("Shaders\\fragment_shader.fshader");
	GLuint fragment_shader = 0;
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragment_shader, 1, &fragment_string, NULL);
	glCompileShader(fragment_shader);

	delete[] fragment_string;

	GLint success;
	GLchar infolog[512];
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragment_shader, sizeof(infolog), NULL, infolog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
	}

	return fragment_shader;
}

GLuint LinkShaderProgram(const GLuint vertex_shader, const GLuint fragment_shader)
{
	GLuint shader_program;
	shader_program = glCreateProgram();

	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	GLint success;
	GLchar infolog[512];
	glGetShaderiv(shader_program, GL_LINK_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(shader_program, sizeof(infolog), NULL, infolog);
		std::cerr << "ERROR::SHADER_PROGRAM::LINK_FAILED\n" << infolog << std::endl;
	}

	return shader_program;
}