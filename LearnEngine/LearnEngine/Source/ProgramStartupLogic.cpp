#include "..\Include\Program\Program.h"
#include "..\Include\Entity\Entity.h"
#include "..\Include\Util\Debugging\DebugTools.h"
#include "..\Resources\Scripts\CameraController.h"
#include "..\Resources\Scripts\Rotator.h"

void Program::StartupLogic()
{
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
    material->SetShader(test_cube_shader);
    material->AddTexture(0, texture_controller);
    display_gl_errors();


    auto* entity = Entity::CreateEntity();
    entity->Transform().Position() = glm::vec3(0.0f, -0.5f, 6.0f);
    auto gl_obj = entity->AddComponent<GLObject>();
    gl_obj->SetMainMaterial(material);
    gl_obj->SetVertexData(vertex_data);


    auto* entity2 = Entity::CreateEntity();
    entity2->Transform().Position() = glm::vec3(2.0f, 0.0f, 3.0f);
    auto gl_obj2 = entity2->AddComponent<GLObject>();
    gl_obj2->SetMainMaterial(material);
    gl_obj2->SetVertexData(vertex_data);

    entity2->AddComponent<Rotator>();
    //entity->AddComponent<CameraController>();

    entity->Transform().Scale().z = 2.0f;

    entity->Name() = "cube_1";
    entity->Name() = "cube_2";

    RenderingSystem::Instance().GetMainCamera().AddComponent<CameraController>();
}