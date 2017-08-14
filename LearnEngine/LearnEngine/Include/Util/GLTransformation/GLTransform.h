#ifndef __GL_TRANSFORM_H__
#define __GL_TRANSFORM_H__

#include <GL\glew.h>
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include <glm\gtc\quaternion.hpp>

class x_type { std::int8_t ch; };
class y_type { std::int8_t ch; };
class z_type { std::int8_t ch; };

// Represents ready-to use transformation interface.
// Stores transformation data on GPU buffer.
// Can bind internal GPU buffer to the conventional uniform binding index.
class GLTransform
{
public:
    // Conventional transfrom data uniform binding index.
    static constexpr GLuint     TRANSFORM_BLOCK_BINDING_INDEX   = 1;
                     
private:             
    static constexpr GLsizei    GPU_BUFFER_SIZE                 = sizeof(glm::mat4);

public:
    // Default constuctor provides allocation of memory
    // on the GPU and some other setup.
    GLTransform();

    // Deletes model matrix buffer from the GPU
    virtual ~GLTransform();
    
    // Binding contents of the internal buffer to the conventional binding index (0).
    // If model matrix in buffer is outdated, updates it.
    // Convention: contents of the transform buffer is model matrix (glm::mat4).
    void                        BindTransformUniformBuffer  ();
   
protected:
    GLTransform                                             (const GLTransform& rhs) = delete;
    GLTransform                                             (GLTransform&& rhs) = delete;
    GLTransform&                operator=                   (GLTransform&& rhs) = delete;

    // Performs deep copy of the transformation properties and the GPU buffer.
    GLTransform&                operator=                   (const GLTransform& rhs);

public:

    const glm::vec3&            Position                    () const;
    glm::vec3&                  Position                    ();

    const glm::quat&            Rotation                    () const;
    glm::quat&                  Rotation                    ();
    glm::vec3                   Euler                       () const;


    const glm::vec3&            Scale                       () const;
    glm::vec3&                  Scale                       ();

    glm::vec3                   Right                       () const;
    glm::vec3                   Up                          () const;
    glm::vec3                   Forward                     () const;


protected:
    // Allocate GPU buffer with appropriate size to hold model matrix data.
    // Now buffer size is (sizeof(glm::mat4x4)).
    void                        AllocateGPUBuffer           ();

    // Update model matrix in the GPU buffer with transformation properties 
    // (position, rotation, scale).
    void                        UpdateBuffer                ();

    // Apply scaling transfromation to the source matrix.
    static void                 ApplyScale                  (glm::mat4* const source, const glm::vec3& scale);

    // Apply rotation transformation to the source matrix.
    static void                 ApplyRotation               (glm::mat4* const source, const glm::quat& quaternion);

    // Apply translation transformation to the source matrix.
    static void                 ApplyTranslation            (glm::mat4* const source, const glm::vec3& position);

protected:
    glm::vec3                   position_;
    glm::vec3                   scale_;
    glm::quat                   rotation_;

    // Flag which reports if the transformation properties were changed
    // and the matrix in the buffer should be updated before rendering.
    bool                        model_mat_outdated_;
    GLuint                      transform_uniform_buffer_handle_;
};

#endif