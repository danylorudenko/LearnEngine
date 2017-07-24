#include "..\Include\Program.h"
#include "..\Include\Util\Input.h"
#include "..\Include\Util\Debugging\DebugTools.h"
#include "..\Include\Entity\Entity.h"
#include "..\Include\World\World.h"

Program::Program()
{
    Initialize();
}

Program::~Program()
{
    World::Delete();
    RenderingSystem::Delete();
    glfwTerminate();
}

void Program::Initialize()
{
    if (InitGLFW() != 0) {
        throw std::runtime_error("Error initializing GLFW");
    }

    // ================

    main_window_ = nullptr;
    if (OpenWindow_SetContext(main_window_, default_resolution_X, default_resolution_Y) != 0) {
        throw std::runtime_error("Error opening window.");
    }

    // ================

    if (InitGLEW() != 0) {
        throw std::runtime_error("Error initializing GLEW.");
    }

    // Callbacks
    glfwSetKeyCallback(main_window_, key_callback);
    glfwSetFramebufferSizeCallback(main_window_, &RenderingSystem::frame_buffer_size_callback);

    // ================

    World::Create();

    auto main_camera = std::make_shared<Camera>(RenderingSystem::DEFAULT_FOW);
    RenderingSystem::Create(default_resolution_X, default_resolution_Y, main_camera);
    

    auto vertex_data = std::shared_ptr<VertexData>(
        new VertexData(
            new GLfloat[180] {
                    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
                     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
                     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

                    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
                    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

                    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
                     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

                    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
                    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
                },
            36,
            sizeof(GLfloat) * 5 * 36,
            sizeof(GLfloat) * 5,
            0
            )
        );

    display_gl_errors();

    VertexAttribData pos_attrib_data(
        0,
        0,
        GL_FLOAT,
        0,
        GL_FALSE,
        sizeof(GLfloat) * 3,
        3
    );
    VertexAttribData uv_attrib_data(
        1,
        1,
        GL_FLOAT,
        sizeof(GLfloat) * 3,
        GL_FALSE,
        sizeof(GLfloat) * 2,
        2
    );

    display_gl_errors();

    vertex_data->AddVAOVertexAttrib(pos_attrib_data);
    vertex_data->AddVAOVertexAttrib(uv_attrib_data);
    
    display_gl_errors();

    auto test_cube_shader = std::make_shared<ShaderProgram>("Shaders\\vertex_shader.vert", "Shaders\\fragment_shader.frag");
    display_gl_errors();
    auto texture_controller = std::shared_ptr<TextureController>(new TextureController("Resources\\container.jpg"));
    display_gl_errors();
    auto material = std::shared_ptr<Material>(new Material(test_cube_shader));
    display_gl_errors();
    material->AddTexture(0, texture_controller);
    display_gl_errors();
    auto* entity = Entity::CreateEntity();
    entity->AddComponent(new GLObject(vertex_data, material));
    
    GLObject* gl_obj = entity->GetComponent<GLObject>();
    gl_obj->SetPosition(0.0f, 0.0f, -3.0f);
}

void Program::StartMainLoop()
{
    while (!glfwWindowShouldClose(main_window_)) {
		glfwPollEvents();

        RenderingSystem::Instance().Iterate(main_window_);
    }
}

void Program::FrameBufferSizeCallBack(GLFWwindow * window, int width, int height)
{
    RenderingSystem::Instance().SetViewport(width, height);
}
