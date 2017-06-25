#ifndef __DEBUG_TOOLS_H__
#define __DEBUG_TOOLS_H__

#define display_gl_errors() _display_gl_errors(__FILE__,__LINE__)

void	_display_gl_errors(const char* file_name, const int line_number);

#endif