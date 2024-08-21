#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"+
#include "ImGui/imgui_impl_opengl3.h"

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>

#include "EditorUI/GUIManager/GUIManager.h"
#include "OpenGL/GlUtils.h"

#include "Math/Vector3/Vector3.h"
#include "OpenGL/Vertex/Vertex.h"
#include "OpenGL/Buffers/Buffer.h"
#include "OpenGL/Entities/Entity.h"
#include "OpenGL/Material/Material.h"
#include "OpenGL/Shaders/Shader.h"
#include "OpenGL/Textures/Texture.h"
#include "OpenGL/World/World.h"
#include "OpenGl/Entities/Camera.h"

int main(void)
{
    GLFWwindow* window;
    if(!InitEngine(window)) //Init all engine systems
    {
        glfwTerminate();
    }

    // std::vector<Vertex> vertices =
    // {
    //     Vertex(Vector3( -0.5f, -0.5f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f)),
    //     Vertex(Vector3(0.5f, -0.5f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f)),
    //     Vertex(Vector3(0.0f,  0.5f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.5f, 1.0f)),
    // };
    //
    // std::vector<unsigned int> indices =
    // {
    //     0,1,2
    // };

    std::vector<Vertex> vertices =
    {
        // Cara delantera
        Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f)),
        Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f)),
        Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f)),
        Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f)),

        // Cara trasera
        Vertex(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f)),
        Vertex(Vector3(0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f)),
        Vertex(Vector3(0.5f, 0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f)),
        Vertex(Vector3(-0.5f, 0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f)),

        // Cara izquierda
        Vertex(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f)),
        Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f)),
        Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f)),
        Vertex(Vector3(-0.5f, 0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f)),

        // Cara derecha
        Vertex(Vector3(0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f)),
        Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f)),
        Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f)),
        Vertex(Vector3(0.5f, 0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f)),

        // Cara superior
        Vertex(Vector3(-0.5f, 0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f)),
        Vertex(Vector3(0.5f, 0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f)),
        Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f),Vector2(1.0f, 1.0f)),
        Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f)),

        // Cara inferior
        Vertex(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f)),
        Vertex(Vector3(0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f)),
        Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f)),
        Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f))
    };

    std::vector<unsigned int> indices =
    {
        // Cara delantera
        0, 1, 2, 2, 3, 0,
        // Cara trasera
        4, 5, 6, 6, 7, 4,
        // Cara izquierda
        8, 9, 10, 10, 11, 8,
        // Cara derecha
        12, 13, 14, 14, 15, 12,
        // Cara superior
        16, 17, 18, 18, 19, 16,
        // Cara inferior
        20, 21, 22, 22, 23, 20
    };
    
    // Shader* basicShader = Shader::Load("Data/Shaders/BasicShader/VertexShader.glsl", "Data/Shaders/BasicShader/FragmentShader.glsl");
    // Shader* texShader = Shader::Load("Data/Shaders/TextureShader/VertexShader.glsl", "Data/Shaders/TextureShader/FragmentShader.glsl");
    Shader* mvpShader = Shader::Load("Data/Shaders/3DShader/VertexShader.glsl", "Data/Shaders/3DShader/FragmentShader.glsl");
    Buffer* myBuffer = new Buffer(vertices, indices);

    Texture* brickTexture = Texture::Load("Data/Textures/wall.jpg");
    Material* brickMaterial = new Material(brickTexture, mvpShader);

    Texture* woodtexture = Texture::Load("Data/Textures/Wood.png");
    std::string woodMaterialName = "Wood Material";
    Material* woodMaterial = new Material(woodtexture, mvpShader, woodMaterialName);

    Entity* myEntity = new Entity(brickMaterial, "Cube1");
    myEntity->SetBuffer(myBuffer);
    World::GetInstance()->AddEntity(myEntity);

    Camera* myCamera = new Camera();
    myCamera->SetPosition(Vector3(0,0,5));
    World::GetInstance()->SetActiveCamera(myCamera);

    // Entity* myEntity2 = new Entity(woodMaterial, "Cube2");
    // myEntity2->SetBuffer(myBuffer);
    // myEntity2->SetPosition(Vector3(2,0,0));
    // World::GetInstance()->AddEntity(myEntity2);

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImFont* font_title = io.Fonts->AddFontFromFileTTF("C:/Users/Carlos/Documents/GitHub/OpenGl/Engine/PixelGL/Dependencies/include/Fonts/Font.ttf", 12.0f, NULL, io.Fonts->GetGlyphRangesDefault()); 
    IM_ASSERT(font_title != NULL);
    
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        World::GetInstance()->Draw();
        GUIManager::GetInstance()->Draw();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
