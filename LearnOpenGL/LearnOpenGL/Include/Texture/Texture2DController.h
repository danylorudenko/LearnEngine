#ifndef __TEXTURE2D_CONTROLLER_H__
#define __TEXTURE2D_CONTROLLER_H__

#include <SOIL\SOIL.h>
#include <GL\glew.h>


class Texture2DController
{
public:
	Texture2DController										(const char* texture_path_1, const char* texture_path_2);

	void						Bind1						();
	void						Bind2						();

private:
	GLuint texture1_;
	GLuint texture2_;
};

#endif