#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>

#include "EditorUI/GUIManager/GUIManager.h"
#include "OpenGL/GlUtils.h"

#include "Math/Vector3/Vector3.h"
#include "OpenGL/Vertex/Vertex.h"
#include "OpenGL/Buffers/Buffer.h"
#include "OpenGL/Buffers/FrameBuffer.h"
#include "OpenGL/Entities/Entity.h"
#include "OpenGL/Material/Material.h"
#include "OpenGL/Shaders/Shader.h"
#include "OpenGL/Textures/Texture.h"
#include "OpenGL/World/World.h"
#include "OpenGl/Entities/Camera.h"
#include "OpenGL/Entities/Light.h"

int main(void)
{
    GLFWwindow* window;
    if(!InitEngine(window)) //Init all engine systems
    {
        glfwTerminate();
    }
    GUIManager::GetInstance()->SetGLFWWindow(window);

    std::vector<Vertex> vertices =
    {
        // Cara delantera
        Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f)),
        Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f)),
        Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f)),
        Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f)),

        // Cara trasera
        Vertex(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)),
        Vertex(Vector3(0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)),
        Vertex(Vector3(0.5f, 0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f)),
        Vertex(Vector3(-0.5f, 0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f)),

        // Cara izquierda
        Vertex(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f)),
        Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f)),
        Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f)),
        Vertex(Vector3(-0.5f, 0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f)),

        // Cara derecha
        Vertex(Vector3(0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f)),
        Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f)),
        Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f)),
        Vertex(Vector3(0.5f, 0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f)),

        // Cara superior
        Vertex(Vector3(-0.5f, 0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f)),
        Vertex(Vector3(0.5f, 0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f)),
        Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f),Vector2(1.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f)),
        Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f)),

        // Cara inferior
        Vertex(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)),
        Vertex(Vector3(0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)),
        Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f)),
        Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f))
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
    Shader* lightSourceShader = Shader::Load("Data/Shaders/LightSourceShader/VertexShader.glsl", "Data/Shaders/LightSourceShader/FragmentShader.glsl");
    Shader* lightShader = Shader::Load("Data/Shaders/LightShader/VertexShader.glsl", "Data/Shaders/LightShader/FragmentShader.glsl");

    Buffer* myBuffer = new Buffer(vertices, indices);

    Texture* brickTextureDiff = Texture::Load("Data/Textures/Box.png");
    Texture* brickTextureSpec = Texture::Load("Data/Textures/BoxSpecular.png");
    Texture* brickTextureEmission = Texture::Load("Data/Textures/matrix.jpg");
    std::string brickMaterialName = "Brick Material";
    Material* brickMaterial = new Material(brickTextureDiff, lightShader, brickMaterialName, Vector3(1.0f, 1.0f, 1.0f), Vector3(1.0f, 1.0f, 1.0f));
    brickMaterial->AddTexture(brickTextureSpec);
    brickMaterial->AddTexture(brickTextureEmission);
    
    Texture* woodtexture = Texture::Load("Data/Textures/Wood.png");
    std::string woodMaterialName = "Wood Material";
    Material* woodMaterial = new Material(woodtexture, lightShader, woodMaterialName, Vector3(1.0f, 1.0f, 1.0f));

    Texture* lightTexture = Texture::Load("Data/Textures/LightTexture.jpg");
    std::string lightMaterialName = "Light Material";
    Material* lightMaterial = new Material(lightTexture, lightSourceShader, lightMaterialName, Vector3(1.0f, 1.0f, 1.0f));

    Entity* cube = new Entity(brickMaterial, "Cube");
    cube->SetBuffer(myBuffer);
    World::GetInstance()->AddEntity(cube);

    Light* light = new Light(lightMaterial, "Light");
    light->SetBuffer(myBuffer);
    light->SetPosition(Vector3(1, 1, 0));
    light->SetScale(Vector3(0.2f, 0.2f, 0.2f));
    World::GetInstance()->AddEntity(light);
    World::GetInstance()->AddLight(light);

    Camera* myCamera = new Camera();
    myCamera->SetPosition(Vector3(0,0,3));
    World::GetInstance()->SetActiveCamera(myCamera);

    // Entity* myEntity2 = new Entity(woodMaterial, "Cube2");
    // myEntity2->SetBuffer(myBuffer);
    // myEntity2->SetPosition(Vector3(2,0,0));
    // World::GetInstance()->AddEntity(myEntity2);

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImFont* font_title = io.Fonts->AddFontFromFileTTF("C:/Users/Carlos/Documents/GitHub/OpenGl/Engine/PixelGL/Dependencies/include/Fonts/Font.ttf", 12.0f, NULL, io.Fonts->GetGlyphRangesDefault()); 
    IM_ASSERT(font_title != NULL);


    FrameBuffer* framebuffer = new FrameBuffer(windowWidth, windowHeight);
    
    while (!glfwWindowShouldClose(window))
    {
        World::GetInstance()->Tick();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        GUIManager::GetInstance()->CreateDockingSpace();
        
        framebuffer->Bind();
        //glViewport(0,0,windowWidth, windowHeight);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT);
        
        World::GetInstance()->Draw();

        framebuffer->Unbind();
        ImGui::Begin("Scene");
        {
            ImGui::BeginChild("GameRender");
            windowWidth = ImGui::GetContentRegionAvail().x;
            windowHeight = ImGui::GetContentRegionAvail().y;
            // framebuffer->RescaleFrameBuffer(windowWidth, windowHeight);
            ImGui::Image(
                (ImTextureID)framebuffer->getFrameTexture(), 
                ImGui::GetContentRegionAvail(), 
                ImVec2(0, 1), 
                ImVec2(1, 0)
            );
            ImGui::EndChild();
        }
        ImGui::End();

        GUIManager::GetInstance()->Tick();
        GUIManager::GetInstance()->Draw();
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

         if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
