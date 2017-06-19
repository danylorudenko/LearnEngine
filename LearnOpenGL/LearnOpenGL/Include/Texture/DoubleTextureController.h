#ifndef __DOUBLE_TEXTURE_CONTROLLER_H__
#define __DOUBLE_TEXTURE_CONTROLLER_H__

#include "TextureController.h"

class DoubleTextureController : public TextureController
{
public:
	DoubleTextureController                                 ();
    DoubleTextureController                                 (const std::string& file1_path_, const std::string& file2_path_);

    virtual void                Bind                        () override;

    virtual void                LoadTextureData             () override;
    virtual void                LoadToGL                    () override;

    virtual void                UnloadFromMemory            () override;
    virtual void                UnloadFromGL                () override;

protected:
    std::string                 file2_path_;

	GLuint                      texture2_handle_;
    unsigned char*              image2_data_;

    int                         width2_;
    int                         height2_;
	
};

#endif