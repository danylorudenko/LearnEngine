#ifndef __SHADER_MANAGER_H__
#define __SHADER_MANAGER_H__

#include <GL\glew.h>
#include <glm\fwd.hpp>
#include <string>

class ShaderProgram
{
public:
    static constexpr char*      MODEL_MATRIX_NAME           = "modelMatrix";
    static constexpr char*      VIEW_MATRIX_NAME            = "viewMatrix";
    static constexpr char*      PERSPECTIVE_MATRIX_NAME     = "perspectiveMatrix";

public:
	ShaderProgram					    (const GLchar* vertex_cource, const GLchar* fragment_source);

	void			Use				    ();

    void            SetIntUniform       (const std::string& name, GLint value);
    void            SetFloatUniform     (const std::string& name, GLfloat value);
    void            SetVec3fUniform     (const std::string& name, glm::vec3& value);
    void            SetVec4fUniform     (const std::string& name, glm::vec4& value);
    void            SetMatrix4Uniform   (const std::string& name, glm::mat4& value);
    void            SetSampler          (const std::string& name, int value);

	GLuint			GetHandle		    ();

	~ShaderProgram					    ();

private:
	GLuint			CompileVertex	    (const GLchar* vertex_source);
	GLuint			CompileFragment	    (const GLchar* fragment_source);
	GLuint			LinkShaders		    (const GLuint vertex_shader, const GLuint fragment_shader);

	std::string		ReadFromFile	    (const GLchar* file_path);

private:
	GLuint			shader_program_handle_;
};

#endif