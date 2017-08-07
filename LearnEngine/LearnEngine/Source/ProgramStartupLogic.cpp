#include "..\Include\Program\Program.h"
#include "..\Include\Entity\Entity.h"
#include "..\Include\Util\Debugging\DebugTools.h"
#include "..\Resources\Scripts\Rotator.h"

void Program::StartupLogic()
{
    //RenderingSystem::Instance().GetMainCamera().SetWorldPosition(glm::vec3(0.0f, 3.0f, -1.0f));
    //RenderingSystem::Instance().GetMainCamera().SetViewDirection(glm::vec3(0.0f, 30.0, 0.0f));

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

    // Draw command initialization
    DrawArraysIndirectCommand draw_command;
    draw_command.SetVertexCount(36);

    vertex_data->SetDrawCommand(std::move(draw_command));

    display_gl_errors();

    auto test_cube_shader = std::make_shared<ShaderProgram>("Resources\\Shaders\\vertex_shader.vert", "Resources\\Shaders\\fragment_shader.frag");
    display_gl_errors();
    auto texture_controller = std::shared_ptr<TextureController>(new TextureController("Resources\\Images\\container.jpg"));
    display_gl_errors();
    auto material = std::shared_ptr<Material>(new Material(test_cube_shader));
    display_gl_errors();
    material->AddTexture(0, texture_controller);
    display_gl_errors();
    auto* entity = Entity::CreateEntity();
    entity->Transform().SetPosition(glm::vec3(0.0f, -0.5f, 6.0f));
    entity->AddComponent(new GLObject(vertex_data, material));

    auto* entity2 = Entity::CreateEntity();
    entity2->Transform().SetPosition(2.0f, 0.0f, 3.0f);
    entity2->AddComponent(new GLObject(vertex_data, material));

    entity->AddComponent(new Rotator());
    entity2->AddComponent(new Rotator());
}