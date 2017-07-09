#ifndef __I_TRANSFORMABLE_H__
#define __I_TRANSFORMABLE_H__

#include <GL\glew.h>
#include <glm\vec3.hpp>

// Represents ready-to use transformation interface.
// Stores transformation data on GPU buffer throught the uniform buffer.
class ITransformable
{
public:
    static constexpr unsigned int TRANSFORM_BLOCK_BINDING_INDEX = 0;

private:
    static constexpr unsigned int POSITION_OFFSET   = 0 * sizeof(glm::vec3);
    static constexpr unsigned int ROTATION_OFFSET   = 1 * sizeof(glm::vec3);
    static constexpr unsigned int SCALE_OFFSET      = 2 * sizeof(glm::vec3);
    static constexpr unsigned int BUFFER_SIZE       = 3 * sizeof(glm::vec3);

public:
    void*                       GetModelMatrix      ();

    glm::vec3                   GetPosition         () const;
    glm::vec3                   GetRotation         () const;
    glm::vec3                   GetScale            () const;

    void                        SetPosition         (glm::vec3& world_position);
    void                        SetPosition         (float x, float y, float z);

    void                        SetScale            (glm::vec3& world_scale);
    void                        SetScale            (float x, float y, float z);

    void                        SetRotation         (glm::vec3& world_rotation_euler);
    void                        SetRotation         (float x, float y, float z);

protected:
    ITransformable                                  (const ITransformable& rhs) = delete;
    ITransformable                                  (ITransformable&& rhs) = delete;
    ITransformable&             operator=           (ITransformable&& rhs) = delete;

    // Default constuctor must be called in all inheriteng classes. It provides allocation of memory
    // on the GPU and some other setup.
    ITransformable                                  ();
    ITransformable&             operator=           (const ITransformable& rhs);

private:
    void                        AllocateBuffer      ();
    void                        FillBuffer          ();
    void                        BindUniformBuffer   ();


private:
    GLuint          uniform_buffer_handle_;
};

#endif