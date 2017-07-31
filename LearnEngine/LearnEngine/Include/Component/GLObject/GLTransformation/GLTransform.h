#ifndef __I_TRANSFORMABLE_H__
#define __I_TRANSFORMABLE_H__

#include <GL\glew.h>
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>

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
    // Binding contents of the internal buffer to the conventional binding index (0).
    // Convention: contents of the transform buffer is model matrix (glm::mat4).
    void                        BindTransformUniformBuffer  () const;
   
protected:
    GLTransform                                             (const GLTransform& rhs) = delete;
    GLTransform                                             (GLTransform&& rhs) = delete;
    GLTransform&                operator=                   (GLTransform&& rhs) = delete;

    // Default constuctor must be called in all inheriteng classes. It provides allocation of memory
    // on the GPU and some other setup.
    GLTransform                                             ();

    // Performs full copy of the GPU buffer to the instance.
    GLTransform&                operator=                   (const GLTransform& rhs);

private:
    // Allocating GPU buffer with appropriate size to hold model matrix data.
    // Now buffer size is (sizeof(glm::mat4x4)).
    void                        AllocateGPUBuffer           ();
    void                        FillGPUBuffer               ();
    void                        UpdateBuffer                ();

    void                        ApplyScale                  (glm::mat4* const source, const glm::vec3& scale);
    void                        ApplyRotation               (glm::mat4* const source, const glm::vec3& euler);
    void                        ApplyTranslation            (glm::mat4* const source, const glm::vec3& position);


private:
    glm::vec3                   position_;
    glm::vec3                   rotation_;
    glm::vec3                   scale_;

    GLuint                      uniform_buffer_handle_;
};

#endif