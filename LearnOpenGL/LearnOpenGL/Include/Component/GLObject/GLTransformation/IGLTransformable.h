#ifndef __I_TRANSFORMABLE_H__
#define __I_TRANSFORMABLE_H__

#include <GL\glew.h>
#include <glm\vec3.hpp>


enum struct POS
{
    X = 0 * sizeof(GLfloat),
    Y = 1 * sizeof(GLfloat),
    Z = 2 * sizeof(GLfloat)
};

enum struct ROT
{
    X = 0 * sizeof(GLfloat),
    Y = 1 * sizeof(GLfloat),
    Z = 2 * sizeof(GLfloat),
};

enum struct SCALE
{
    X = 0 * sizeof(GLfloat),
    Y = 1 * sizeof(GLfloat),
    Z = 2 * sizeof(GLfloat),
};


// Represents ready-to use transformation interface.
// Stores transformation data on GPU buffer.
// Can bind internal GPU buffer to the conventional uniform binding index.
class IGLTransformable
{
public:
    // Conventional transfrom data uniform binding index.
    static constexpr unsigned int TRANSFORM_BLOCK_BINDING_INDEX = 0;

private:
    static constexpr unsigned int GPU_BUFFER_SIZE       = 3 * sizeof(glm::vec3);

    static constexpr unsigned int GPU_POSITION_OFFSET   = 0 * sizeof(glm::vec3);
    static constexpr unsigned int GPU_ROTATION_OFFSET   = 1 * sizeof(glm::vec3);
    static constexpr unsigned int GPU_SCALE_OFFSET      = 2 * sizeof(glm::vec3);

public:
    // Binding contents of the internal buffer to the conventional binding index (0).
    // Convention: contents of the buffer are (3 * glm::vec3):
    //      position    :   glm::vec3
    //      rotation    :   glm::vec3
    //      scale       :   glm::vec3
    void                        BindUniformBuffer   ();
    
    // Extracts contents of the GPU buffer, constructing glm::vec3 representation of position.
    glm::vec3                   GetPosition         () const;

    // Extracts contents of the GPU buffer, constructing glm::vec3 representation of rotation.
    glm::vec3                   GetRotation         () const;

    // Extracts contents of the GPU buffer, constructing glm::vec3 representation of scale.
    glm::vec3                   GetScale            () const;


    void                        SetPosition         (const glm::vec3& world_position);
    void                        SetPosition         (GLfloat x, GLfloat y, GLfloat z);
    void                        SetPosParam         (POS p_name, GLfloat param);

    void                        SetRotation         (const glm::vec3& world_rotation_euler);
    void                        SetRotation         (GLfloat x, GLfloat y, GLfloat z);
    void                        SetRotParam         (ROT p_name, const GLfloat param);

    void                        SetScale            (const glm::vec3& world_scale);
    void                        SetScale            (GLfloat x, GLfloat y, GLfloat z);
    void                        SetScaleParam       (SCALE p_name, GLfloat param);

protected:
    IGLTransformable                                (const IGLTransformable& rhs) = delete;
    IGLTransformable                                (IGLTransformable&& rhs) = delete;
    IGLTransformable&           operator=           (IGLTransformable&& rhs) = delete;

    // Default constuctor must be called in all inheriteng classes. It provides allocation of memory
    // on the GPU and some other setup.
    IGLTransformable                                ();

    // Performs full copy of the GPU buffer to the instance.
    IGLTransformable&           operator=           (const IGLTransformable& rhs);

private:
    // Allocating GPU buffer with appropriate size to hold transformation data.
    // Now buffer size is (3 * sizeof(glm::vec3).
    void                        AllocateGPUBuffer   ();
    void                        FillGPUBuffer       ();


private:
    GLuint                      uniform_buffer_handle_;
};

#endif