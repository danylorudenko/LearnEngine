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
    // Default constuctor must be called in all inheriteng classes. It provides allocation of memory
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

    // Performs full copy of the GPU buffer to the instance.
    GLTransform&                operator=                   (const GLTransform& rhs);

public:
    void                        SetPosition                 (const glm::vec3& world_position);
    void                        SetPosition                 (GLfloat x, GLfloat y, GLfloat z);
    void                        SetPosition                 (x_type, GLfloat param);
    void                        SetPosition                 (y_type, GLfloat param);
    void                        SetPosition                 (z_type, GLfloat param);

    void                        SetRotation                 (const glm::vec3& world_rotation_euler);
    void                        SetRotation                 (GLfloat x, GLfloat y, GLfloat z);
    void                        SetRotation                 (x_type, GLfloat param);
    void                        SetRotation                 (y_type, GLfloat param);
    void                        SetRotation                 (z_type, GLfloat param);

    void                        SetScale                    (const glm::vec3& world_scale);
    void                        SetScale                    (GLfloat x, GLfloat y, GLfloat z);
    void                        SetScale                    (x_type, GLfloat param);
    void                        SetScale                    (y_type, GLfloat param);
    void                        SetScale                    (z_type, GLfloat param);

    const glm::vec3&            GetPosition                 () const;
    const glm::vec3&            GetRotation                 () const;
    const glm::vec3&            GetScale                    () const;


protected:
    // Allocating GPU buffer with appropriate size to hold model matrix data.
    // Now buffer size is (sizeof(glm::mat4x4)).
    void                        AllocateGPUBuffer           ();
    void                        FillGPUBuffer               ();
    void                        UpdateBuffer                ();

    static void                 ApplyScale                  (glm::mat4* const source, const glm::vec3& scale);
    static void                 ApplyRotation               (glm::mat4* const source, const glm::vec3& euler);
    static void                 ApplyTranslation            (glm::mat4* const source, const glm::vec3& position);


protected:
    glm::vec3                   position_;
    glm::vec3                   rotation_;
    glm::vec3                   scale_;

    bool                        model_mat_outdated_;
    GLuint                      transform_uniform_buffer_handle_;
};

#endif