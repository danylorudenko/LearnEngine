#include "..\Include\Util\Debugging\DebugTools.h"

#include <gl\glew.h>
#include <iostream>
#include <fstream>

#define __GL_CONSOLE_DEBUG__

void _display_gl_errors(const char* file_name, const int line_number)
{
#ifdef __GL_FILE_DEBUG__
	std::ofstream debug_stream("debug_log.txt", std::ios_base::app | std::ios_base::out);
#define OUTPUT_STREAM debug_stream
#endif

#ifdef __GL_CONSOLE_DEBUG__
#define OUTPUT_STREAM std::cerr
#endif

	GLenum error_code;

	do {
		error_code = glGetError();

		switch (error_code) {
		case GL_INVALID_ENUM:
			OUTPUT_STREAM << "GL::ERROR::GL_INVALID_ENUM" << std::endl << "(file: " << file_name << ". line: " << line_number << ")" << std::endl;
			break;
		case GL_INVALID_VALUE:
			OUTPUT_STREAM << "GL::ERROR::GL_INVALID_VALUE" << std::endl << "(file: " << file_name << ". line: " << line_number << ")" << std::endl;;
			break;
		case GL_INVALID_OPERATION:
			OUTPUT_STREAM << "GL::ERROR::GL_INVALID_OPERATION" << std::endl << "(file: " << file_name << ". line: " << line_number << ")" << std::endl;
			break;
		case GL_STACK_OVERFLOW:
			OUTPUT_STREAM << "GL::ERROR::GL_STACK_OVERFLOW" << std::endl << "(file: " << file_name << ". line: " << line_number << ")" << std::endl;
			break;
		case GL_STACK_UNDERFLOW:
			OUTPUT_STREAM << "GL::ERROR::GL_STACK_UNDERFLOW" << std::endl << "(file: " << file_name << ". line: " << line_number << ")" << std::endl;
			break;
		case GL_OUT_OF_MEMORY:
			OUTPUT_STREAM << "GL::ERROR::GL_OUT_OF_MEMORY" << std::endl << "(file: " << file_name << ". line: " << line_number << ")" << std::endl;
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			OUTPUT_STREAM << "GL::ERROR::GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl << "(file: " << file_name << ". line: " << line_number << ")" << std::endl;
			break;
		case GL_CONTEXT_LOST:
			OUTPUT_STREAM << "GL::ERROR::GL_CONTEXT_LOST" << std::endl << "(file: " << file_name << ". line: " << line_number << ")" << std::endl;
			break;
		case GL_TABLE_TOO_LARGE:
			OUTPUT_STREAM << "GL::ERROR::GL_TABLE_TOO_LARGE" << std::endl << "(file: " << file_name << ". line: " << line_number << ")" << std::endl;
			break;
		}
	}
	while(error_code != GL_NO_ERROR);

#ifdef __GL_FILE_DEBUG__
	OUTPUT_STREAM.close();
#endif
}