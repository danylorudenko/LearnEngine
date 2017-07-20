#ifndef __I_TRANSFORMABLE_H__
#define __I_TRANSFORMABLE_H__

#include <GL\glew.h>
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>

class x_type { char ch; };
class y_type { char ch; };
class z_type { char ch; };

// Represents ready-to use transformation interface.
// Stores transformation data on GPU buffer.
// Can bind internal GPU buffer to the conventional uniform binding index.
class IGLTransformable
{
public:
    // Conventional transfrom data uniform binding index.
    static constexpr GLuint     TRANSFORM_BLOCK_BINDING_INDEX   = 1;
                     
private:             
    static constexpr GLsizei    GPU_BUFFER_SIZE                 = sizeof(glm::mat4);

public:
    // Binding contents of the internal buffer to the conventional binding index (0).
    // Convention: contents of the transform buffer is model matrix (glm::mat4).
    void                        BindTransformUniformBuffer  () const;
    
    // Extracts contents of the GPU buffer, constructing glm::vec3 representation of position.
    glm::vec3                   GetPosition                 () const;

    // Extracts contents of the GPU buffer, constructing glm::vec3 representation of rotation.
    glm::vec3                   GetRotation                 () const;

    // Extracts contents of the GPU buffer, constructing glm::vec3 representation of scale.
    glm::vec3                   GetScale                    () const;


    void                        SetPosition                 (const glm::vec3& world_position);
    void                        SetPosition                 (GLfloat x, GLfloat y, GLfloat z);
    void                        SetPosParam                 (x_type, GLfloat param);
    void                        SetPosParam                 (y_type, GLfloat param);
    void                        SetPosParam                 (z_type, GLfloat param);

    void                        SetRotation                 (const glm::vec3& world_rotation_euler);
    void                        SetRotation                 (GLfloat x, GLfloat y, GLfloat z);
    void                        SetRotParam                 (x_type, GLfloat param);
    void                        SetRotParam                 (y_type, GLfloat param);
    void                        SetRotParam                 (z_type, GLfloat param);

    void                        SetScale                    (const glm::vec3& world_scale);
    void                        SetScale                    (GLfloat x, GLfloat y, GLfloat z);
    void                        SetScaleParam               (x_type, GLfloat param);
    void                        SetScaleParam               (y_type, GLfloat param);
    void                        SetScaleParam               (z_type, GLfloat param);

protected:
    IGLTransformable                                        (const IGLTransformable& rhs) = delete;
    IGLTransformable                                        (IGLTransformable&& rhs) = delete;
    IGLTransformable&           operator=                   (IGLTransformable&& rhs) = delete;

    // Default constuctor must be called in all inheriteng classes. It provides allocation of memory
    // on the GPU and some other setup.
    IGLTransformable                                        ();

    // Performs full copy of the GPU buffer to the instance.
    IGLTransformable&           operator=                   (const IGLTransformable& rhs);

private:
    // Allocating GPU buffer with appropriate size to hold model matrix data.
    // Now buffer size is (3 * sizeof(glm::vec3).
    void                        AllocateGPUBuffer           ();
    void                        FillGPUBuffer               ();


private:
    glm::vec3                   position_;
    glm::vec3                   rotation_;
    glm::vec3                   scale_;

    GLuint                      uniform_buffer_handle_;
};

#endif