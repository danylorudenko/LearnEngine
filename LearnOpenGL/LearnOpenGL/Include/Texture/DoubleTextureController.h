#ifndef __DOUBLE_TEXTURE_CONTROLLER_H__
#define __DOUBLE_TEXTURE_CONTROLLER_H__

#include <SOIL\SOIL.h>
#include <GL\glew.h>


class DoubleTextureController
{
public:
	DoubleTextureController										(const char* texture_path_1, const char* texture_path_2);

    void                        Bind                        ();
	void						Bind1						();
	void						Bind2						();

private:
	GLuint texture1_;
	GLuint texture2_;
};

#endif