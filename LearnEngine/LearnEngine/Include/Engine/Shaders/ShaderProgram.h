#ifndef __SHADER_MANAGER_H__
#define __SHADER_MANAGER_H__

#include <GL\glew.h>
#include <glm\fwd.hpp>
#include <string>

namespace Engine
{

// Wrapper around OpenGL shader program.
// Has accessors to various unifrom setting functions.
class ShaderProgram
{
public:
    // Conventional indicies of standard uniform blocks.
    static constexpr GLint REND_SYSTEM_BIND_INDEX   = 0;
    static constexpr GLint MODEL_BLOCK_BIND_INDEX   = 1;
    static constexpr GLint TEXT_BLOCK_BIND_INDEX    = 2;

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

protected:
	GLuint			CompileVertex	    (const GLchar* vertex_source);
	GLuint			CompileFragment	    (const GLchar* fragment_source);
	GLuint			LinkShaders		    (const GLuint vertex_shader, const GLuint fragment_shader);

    // Read file as a single string to pass to the OpenGL shader program.
	std::string		ReadFile	        (const GLchar* file_path);

protected:
	GLuint			shader_program_handle_;
};

} // namespace Engine

#endif