#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <Engine\Util\GLTransformation\GLTransform.h>
#include <Engine\Util\Debugging\DebugTools.h>

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
    DestroyBuffer();
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
    glm::vec4 forward = rotation_ *  glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
    return glm::vec3(forward.x, forward.y, forward.z);
}

glm::vec3 GLTransform::Up() const
{
    glm::vec4 forward = rotation_ *  glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
    return glm::vec3(forward.x, forward.y, forward.z);
}

glm::vec3 GLTransform::Forward() const
{
    glm::vec4 forward = rotation_ *  glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
    return glm::vec3(forward.x, forward.y, forward.z);
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
    ApplyRotation(&identity_matrix, rotation_);
    ApplyScale(&identity_matrix, scale_);

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

void GLTransform::DestroyBuffer()
{
    glDeleteBuffers(1, &transform_uniform_buffer_handle_);
}

inline void GLTransform::ApplyScale(glm::mat4* const source, const glm::vec3& scale)
{
    *source = glm::scale(*source, scale);
}

inline void GLTransform::ApplyRotation(glm::mat4* const source, const glm::quat& quaternion)
{
   *source *= glm::mat4_cast(quaternion);
}

inline void GLTransform::ApplyTranslation(glm::mat4* const source, const glm::vec3& position)
{
    *source = glm::translate(*source, position);
}