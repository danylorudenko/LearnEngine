#ifndef __SHADER_UTIL_H__
#define __SHADER_UTIL_H__

#include <string>

#include <GL\glew.h>

GLchar* ReadStringFromFile(const std::string& file_name);

GLuint CompileVertexShader();

GLuint CompileFragmentShader();

GLuint LinkShaderProgram(const GLuint vertex_shader, const GLuint fragment_shader);

#endif