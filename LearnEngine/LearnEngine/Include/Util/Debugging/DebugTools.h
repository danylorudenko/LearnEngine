#ifndef __DEBUG_TOOLS_H__
#define __DEBUG_TOOLS_H__

#ifdef __GL_DEBUG__
#define display_gl_errors() _display_gl_errors(__FILE__,__LINE__)
#else
#define display_gl_errors()
#endif

void	_display_gl_errors(const char* file_name, const int line_number);

#endif