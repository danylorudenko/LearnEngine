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

void GLTransform::SetPosition(const glm::vec3 & world_position)
{
    position_ = world_position;
    model_mat_outdated_ = true;
}

void GLTransform::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
    position_.x = x;
    position_.y = y;
    position_.z = z;

    model_mat_outdated_ = true;
}

void GLTransform::SetPosition(x_type, GLfloat param)
{
    position_.x = param;
    model_mat_outdated_ = true;
}

void GLTransform::SetPosition(y_type, GLfloat param)
{
    position_.y = param;
    model_mat_outdated_ = true;
}

void GLTransform::SetPosition(z_type, GLfloat param)
{
    position_.z = param;
    model_mat_outdated_ = true;
}

void GLTransform::SetRotation(const glm::vec3 & world_rotation_euler)
{
    rotation_ = glm::quat(glm::radians(world_rotation_euler));
    model_mat_outdated_ = true;
}

void GLTransform::SetRotation(GLfloat x, GLfloat y, GLfloat z)
{
    rotation_ = glm::quat(glm::radians(glm::vec3(x, y, z)));

    model_mat_outdated_ = true;
}

void GLTransform::SetRotation(x_type, GLfloat param)
{
    glm::vec3 current_rotation = GetEuler();
    current_rotation.x = param;
    rotation_ = glm::quat(glm::radians(current_rotation));
    model_mat_outdated_ = true;
}

void GLTransform::SetRotation(y_type, GLfloat param)
{
    glm::vec3 current_rotation = GetEuler();
    current_rotation.y = param;
    rotation_ = glm::quat(glm::radians(current_rotation));
    model_mat_outdated_ = true;
}

void GLTransform::SetRotation(z_type, GLfloat param)
{
    glm::vec3 current_rotation = GetEuler();
    current_rotation.z = param;
    rotation_ = glm::quat(glm::radians(current_rotation));
    model_mat_outdated_ = true;
}

void GLTransform::SetRotation(const glm::quat & quaternion)
{
    rotation_ = quaternion;
}

void GLTransform::SetScale(const glm::vec3 & world_scale)
{
    scale_ = world_scale;
    model_mat_outdated_ = true;
}

void GLTransform::SetScale(GLfloat x, GLfloat y, GLfloat z)
{
    scale_.x = x;
    scale_.y = y;
    scale_.z = z;

    model_mat_outdated_ = true;
}

void GLTransform::SetScale(x_type, GLfloat param)
{
    scale_.x = param;
    model_mat_outdated_ = true;
}

void GLTransform::SetScale(y_type, GLfloat param)
{
    scale_.y = param;
    model_mat_outdated_ = true;
}

void GLTransform::SetScale(z_type, GLfloat param)
{
    scale_.z = param;
    model_mat_outdated_ = true;
}

const glm::vec3 & GLTransform::GetPosition() const
{
    return position_;
}

glm::vec3 GLTransform::GetEuler() const
{
    return glm::degrees(glm::eulerAngles(rotation_));
}

const glm::quat & GLTransform::GetRotation() const
{
    return rotation_;
}

const glm::vec3 & GLTransform::GetScale() const
{
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