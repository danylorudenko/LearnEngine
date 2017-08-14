#include "..\Include\Util\GLTransformation\GLTransform.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "..\Include\Util\Debugging\DebugTools.h"

GLTransform::GLTransform() : 
    position_(0.0f),
    rotation_(1.0f, 0.0f, 0.0f, 0.0f),
    scale_(1.0f),
    model_mat_outdated_(true)
{
    AllocateGPUBuffer();
}

GLTransform::~GLTransform()
{
    glDeleteBuffers(1, &transform_uniform_buffer_handle_);
}

GLTransform& GLTransform::operator=(const GLTransform& rhs)
{
#ifdef GL44
    
    glBindBuffer(GL_COPY_READ_BUFFER, rhs.transform_uniform_buffer_handle_);
    glBindBuffer(GL_COPY_WRITE_BUFFER, transform_uniform_buffer_handle_);

    glCopyBufferSubData(
        GL_COPY_READ_BUFFER,
        GL_COPY_WRITE_BUFFER,
        0,
        0,
        GPU_BUFFER_SIZE
    );

    display_gl_errors();

#else

    glCopyNamedBufferSubData(
        rhs.transform_uniform_buffer_handle_,
        transform_uniform_buffer_handle_,
        0,
        0,
        GPU_BUFFER_SIZE
    );

#endif
    
    position_ = rhs.position_;
    rotation_ = rhs.rotation_;
    scale_ = rhs.scale_;
    
    return *this;
}

const glm::vec3 & GLTransform::Position() const
{
    return position_;
}

glm::vec3& GLTransform::Position()
{
    model_mat_outdated_ = true;
    return position_;
}

glm::vec3 GLTransform::Euler() const
{
    return glm::degrees(glm::eulerAngles(rotation_));
}

const glm::quat& GLTransform::Rotation() const
{
    return rotation_;
}

glm::quat& GLTransform::Rotation()
{
    model_mat_outdated_ = true;
    return rotation_;
}

const glm::vec3& GLTransform::Scale() const
{
    return scale_;
}

glm::vec3& GLTransform::Scale()
{
    model_mat_outdated_ = true;
    return scale_;
}

glm::vec3 GLTransform::Right() const
{
    GLfloat short_hypothenuse = std::cosf(glm::radians(rotation_.x));
    glm::vec3 direction(
        std::cosf(glm::radians(rotation_.x)) * short_hypothenuse,
        std::sinf(glm::radians(rotation_.y)),
        std::sinf(glm::radians(rotation_.x)) * short_hypothenuse
    );

    return direction;
}

glm::vec3 GLTransform::Up() const
{
    GLfloat short_hypothenuse = std::cosf(glm::radians(rotation_.x));
    glm::vec3 direction(
        std::sinf(glm::radians(rotation_.y)) * short_hypothenuse,
        std::sinf(glm::radians(rotation_.x)),
        std::cosf(glm::radians(rotation_.y)) * short_hypothenuse
    );

    return direction;
}

glm::vec3 GLTransform::Forward() const
{
    GLfloat short_hypothenuse = std::cosf(glm::radians(rotation_.x));
    glm::vec3 direction(
        std::sinf(glm::radians(rotation_.y)) * short_hypothenuse,
        std::sinf(glm::radians(rotation_.x)),
        std::cosf(glm::radians(rotation_.y)) * short_hypothenuse
    );

    return direction;
}

void GLTransform::AllocateGPUBuffer()
{
    glCreateBuffers(1, &transform_uniform_buffer_handle_);

#ifdef GL44

    glBindBuffer(GL_UNIFORM_BUFFER, transform_uniform_buffer_handle_);
    glBufferStorage(GL_UNIFORM_BUFFER, GPU_BUFFER_SIZE, nullptr, GL_DYNAMIC_STORAGE_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);

    display_gl_errors();

#else

    glNamedBufferStorage(transform_uniform_buffer_handle_, GPU_BUFFER_SIZE, nullptr, GL_DYNAMIC_STORAGE_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);

#endif
}

void GLTransform::BindTransformUniformBuffer()
{
    if (model_mat_outdated_) {
        UpdateBuffer();
    }
    glBindBufferBase(GL_UNIFORM_BUFFER, TRANSFORM_BLOCK_BINDING_INDEX, transform_uniform_buffer_handle_);
}

void GLTransform::UpdateBuffer()
{
    glm::mat4 identity_matrix(
        glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
        glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
        glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
    );

    ApplyTranslation(&identity_matrix, position_);
    ApplyScale(&identity_matrix, scale_);
    ApplyRotation(&identity_matrix, rotation_);

#ifdef GL44

    glBindBuffer(GL_UNIFORM_BUFFER, transform_uniform_buffer_handle_);
    glBufferSubData(
        GL_UNIFORM_BUFFER,
        0,
        sizeof(identity_matrix),
        glm::value_ptr(identity_matrix)
    );

    display_gl_errors();

#else

    glNamedBufferSubData(
        transform_uniform_buffer_handle_,
        0,
        sizeof(identity_matrix),
        glm::value_ptr(identity_matrix)
    );

#endif

    model_mat_outdated_ = false;
}

inline void GLTransform::ApplyScale(glm::mat4* const source, const glm::vec3& scale)
{
    *source = glm::scale(*source, scale);
}

inline void GLTransform::ApplyRotation(glm::mat4* const source, const glm::quat& quaternion)
{
    /*static const glm::vec3 X_AXIS(1.0f, 0.0f, 0.0f);
    static const glm::vec3 Y_AXIS(0.0f, 1.0f, 0.0f);
    static const glm::vec3 Z_AXIS(0.0f, 0.0f, 1.0f);
    
    *source = glm::rotate(*source, glm::radians(euler.x), X_AXIS);
    *source = glm::rotate(*source, glm::radians(euler.y), Y_AXIS);
    *source = glm::rotate(*source, glm::radians(euler.z), Z_AXIS);*/

   *source *= glm::mat4_cast(quaternion);
}

inline void GLTransform::ApplyTranslation(glm::mat4* const source, const glm::vec3& position)
{
    *source = glm::translate(*source, position);
}