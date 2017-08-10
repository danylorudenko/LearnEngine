#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <GLFW\glfw3.h>

#include "..\Component.h"
#include "..\ComponentFactory.h"

class Light : public Component
{
protected:
    Light                                   ();
    friend class ComponentFactory<Light>;

public:
    
    Light                                   (const Light& rhs) = delete;
    Light                                   (Light&& rhs) = delete;
    Light&              operator=           (const Light& rhs) = delete;
    Light&              operator=           (Light&& rhs) = delete;

    GLuint              BufferOffset        () const;

    GLfloat             GetIntensity        () const;
    GLfloat             GetRange            () const;

    virtual void        SetIntensity        (GLfloat intensity);
    virtual void        SetRange            (GLfloat intensity);


protected:

    virtual void RegisterInSystem           () override;
    virtual void UnregisterFromSystem       () override;

protected:
    GLuint              buffer_offset_;

    GLfloat             intensity_;
    GLfloat             range_;

};

#endif