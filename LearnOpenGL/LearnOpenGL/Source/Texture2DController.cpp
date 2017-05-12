#include "..\Include\Texture\Texture2DController.h"

Texture2DController::Texture2DController(const char* texture_path_1, const char* texture_path_2)
{
	int width1, height1;
	unsigned char* image_data_1 = SOIL_load_image(texture_path_1, &width1, &height1, 0, SOIL_LOAD_RGB);

	int width2, height2;
	unsigned char* image_data_2 = SOIL_load_image(texture_path_2, &width2, &height2, 0, SOIL_LOAD_RGB);
	
	glGenTextures(1, &texture1_);
	glGenTextures(1, &texture2_);
	glBindTexture(GL_TEXTURE_2D, texture1_);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data_1);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture2_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data_2);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);


	SOIL_free_image_data(image_data_1);
	SOIL_free_image_data(image_data_2);
}

void Texture2DController::Bind1()
{
	glBindTexture(GL_TEXTURE_2D, texture1_);
}

void Texture2DController::Bind2()
{
	glBindTexture(GL_TEXTURE_2D, texture2_);
}