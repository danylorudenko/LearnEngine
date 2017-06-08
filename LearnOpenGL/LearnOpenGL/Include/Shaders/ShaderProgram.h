#ifndef __SHADER_MANAGER_H__
#define __SHADER_MANAGER_H__

#include <GL\glew.h>

#include <string>

class ShaderProgram
{
public:
	ShaderProgram					(const GLchar* vertex_cource, const GLchar* fragment_source);

	void			Use				();

    void            SetIntUniform   (const std::string& name, GLint value);
    void            SetFloatUniform (const std::string& name, GLfloat value);

	GLuint			GetProgram		();

	~ShaderProgram					();

private:
	GLuint			CompileVertex	(const GLchar* vertex_source);
	GLuint			CompileFragment	(const GLchar* fragment_source);
	GLuint			LinkShaders		(const GLuint vertex_shader, const GLuint fragment_shader);

	std::string		ReadFromFile	(const GLchar* file_path);

private:
	GLuint			program_;
};

#endif