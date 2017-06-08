#include "..\Include\Shaders\ShaderProgram.h"

#include <fstream>
#include <iostream>

ShaderProgram::ShaderProgram(const GLchar* vertex_source_file, const GLchar* fragment_source_file)
{
	std::string vertex_source = ReadFromFile(vertex_source_file);
	std::string fragment_source = ReadFromFile(fragment_source_file);

	GLuint vertex_shader = CompileVertex(vertex_source.c_str());
	GLuint fragment_shader = CompileFragment(fragment_source.c_str());

	program_ = LinkShaders(vertex_shader, fragment_shader);

	glDeleteShader(fragment_shader);
	glDeleteShader(vertex_shader);
}

void ShaderProgram::Use()
{
	glUseProgram(program_);
}

void ShaderProgram::SetIntUniform(const std::string& name, GLint value)
{
    GLint uniform_handle = glGetUniformLocation(program_, name.c_str());
    glUniform1i(uniform_handle, value);
}

void ShaderProgram::SetFloatUniform(const std::string& name, GLfloat value)
{
    GLint uniform_handle = glGetUniformLocation(program_, name.c_str());
    glUniform1f(uniform_handle, value);
}

GLuint ShaderProgram::GetProgram()
{
	return program_;
}

GLuint ShaderProgram::CompileVertex(const GLchar* vertex_source)
{
	GLuint vertex_shader = 0;
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertex_shader, 1, &vertex_source, nullptr);
	glCompileShader(vertex_shader);

	GLint success;
	GLchar infolog[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertex_shader, sizeof(infolog), NULL, infolog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << std::endl;
	}

	return vertex_shader;
}

GLuint ShaderProgram::CompileFragment(const GLchar* fragment_source)
{
	GLuint fragment_shader = 0;
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragment_shader, 1, &fragment_source, nullptr);
	glCompileShader(fragment_shader);

	GLint success;
	GLchar infolog[512];
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragment_shader, sizeof(infolog), NULL, infolog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
	}

	return fragment_shader;
}

GLuint ShaderProgram::LinkShaders(const GLuint vertex_shader, const GLuint fragment_shader)
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

std::string ShaderProgram::ReadFromFile(const GLchar* file_name)
{
	std::ifstream in_stream(file_name, std::ios_base::in);

	if (!in_stream.is_open()) {
		throw std::invalid_argument("No such file or directory.");
	}

	in_stream.seekg(0, std::ios_base::end);
	int file_length = static_cast<int>(in_stream.tellg());
	in_stream.seekg(0, std::ios_base::beg);

	std::string file_content;
	std::string buffer;

	while (std::getline(in_stream, buffer)) {
		file_content.append(buffer);
		file_content.append("\n");
	}

	in_stream.close();

	return file_content;
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(program_);
}