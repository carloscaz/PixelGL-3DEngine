#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>

#include "EditorUI/GUIManager/GUIManager.h"
#include "OpenGL/GlUtils.h"

#include "Math/Vector3/Vector3.h"
#include "OpenGL/Buffers/FrameBuffer.h"
#include "OpenGL/Entities/Entity.h"
#include "OpenGL/World/World.h"
#include "OpenGl/Entities/Camera.h"
#include "OpenGL/Entities/Lights/DirectionalLight.h"
#include "OpenGL/Material/Material.h"
#include "OpenGL/Shaders/Shader.h"

void CreateSceneDemo()
{
    GLUtils::CreateCube();
    GLUtils::CreatePointLight();
    GLUtils::CreateDirectionalLight();
}
int main(void)
{
    GLFWwindow* window;
    if(!InitEngine(window)) //Init all engine systems
    {
        glfwTerminate();
    }
    GUIManager::GetInstance()->SetGLFWWindow(window);
    
    //Texture* woodtexture = Texture::Load("Data/Textures/Wood.png");
    //std::string woodMaterialName = "Wood Material";
    //Material* woodMaterial = new Material(woodtexture, lightShader, woodMaterialName, Vector3(1.0f, 1.0f, 1.0f));

    //CreateSceneDemo();
    
    Camera* myCamera = new Camera();
    myCamera->SetPosition(Vector3(0,0,3));
    World::GetInstance()->SetActiveCamera(myCamera);

    // Entity* myEntity2 = new Entity(woodMaterial, "Cube2");
    // myEntity2->SetBuffer(myBuffer);
    // myEntity2->SetPosition(Vector3(2,0,0));
    // World::GetInstance()->AddEntity(myEntity2);

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    
    FrameBuffer* framebuffer = new FrameBuffer(windowWidth, windowHeight);
    
    double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window))
    {
        // get delta time
        float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
        lastTime = glfwGetTime();
        
        World::GetInstance()->Tick();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        GUIManager::GetInstance()->CreateDockingSpace();
        //ImGui::ShowDemoWindow();
        
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

        ImGui::Begin("Performance Window");
        ImGui::Text("DeltaTime: %f", deltaTime);
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

    delete World::GetInstance();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}


