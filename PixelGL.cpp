#include <iostream>

#include "Dependencies/include/ImGui/imgui.h"
#include "Dependencies/include/ImGui/imgui_impl_glfw.h"
#include "Dependencies/include/ImGui/imgui_impl_opengl3.h"
#include "Dependencies/include/glad/glad.h"
#include "Dependencies/include/GLFW/glfw3.h"
#include "EditorUI/GUIManager/GUIManager.h"

#include "Math/Vector3/Vector3.h"
#include "OpenGL/GlUtils.h"
#include "OpenGL/Buffers/FrameBuffer.h"
#include "OpenGL/Entities/Entity.h"
#include "OpenGL/World/World.h"
#include "OpenGl/Entities/Camera.h"
#include "OpenGL/Material/Material.h"
#include "OpenGL/Material/SkyboxMaterial.h"
#include "OpenGL/Shaders/Shader.h"
#include "OpenGL/Skybox/Skybox.h"

//Basic demo scene of engine
void CreateSceneDemo()
{
    //GLUtils::CreateCube();
    //GLUtils::CreatePointLight();
    GLUtils::CreateDirectionalLight();

    //Setting skybox
    Shader* skyShader = Shader::Load("Data/Shaders/SkyboxShader/VertexShader.glsl",
                                  "Data/Shaders/SkyboxShader/FragmentShader.glsl");
    std::vector<std::string> faces
    {
        "Data/Textures/right.jpg",
        "Data/Textures/left.jpg",
        "Data/Textures/top.jpg",
        "Data/Textures/bottom.jpg",
        "Data/Textures/front.jpg",
        "Data/Textures/back.jpg"
    };
    Texture* cubemapTex = Texture::LoadCubeMap(faces);
    SkyboxMaterial* skyMat = new SkyboxMaterial(cubemapTex, skyShader);
    Skybox* sky = new Skybox(skyMat);
    World::GetInstance()->SetSkybox(sky);
}
int main(void)
{
    //Init all engine systems
    GLFWwindow* window;
    if(!InitEngine(window)) 
    {
        glfwTerminate();
    }
    GUIManager::GetInstance()->SetGLFWWindow(window);

    //Create camera
    Camera* myCamera = new Camera();
    myCamera->SetPosition(Vector3(0,0,3));
    World::GetInstance()->SetActiveCamera(myCamera);

    //Setting GLFW framebuffer
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    FrameBuffer* framebuffer = new FrameBuffer(windowWidth, windowHeight);
    double lastTime = glfwGetTime();
    
    CreateSceneDemo();
    while (!glfwWindowShouldClose(window))
    {
        //Get delta time
        float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
        lastTime = glfwGetTime();

        //Tick entities of the world
        World::GetInstance()->GetActiveCamera()->Tick(deltaTime);
        if(World::GetInstance()->GetWorldTick())
        {
            World::GetInstance()->Tick(deltaTime);
        }

        //Create ImGui windows
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

        //Draw all entities of the world
        World::GetInstance()->Draw();

        framebuffer->Unbind();

        //ImGui Scene window
        ImGui::Begin("Scene");
        {
            //Enable Play button if world is not ticking
            ImGui::Indent(600);
            if(!World::GetInstance()->GetWorldTick())
            {
                if(ImGui::Button("Play", ImVec2(100, 20)))
                {
                    World::GetInstance()->SetWorldTick(true);
                    World::GetInstance()->Init();
                }
            }

            //Disable Play button if world is ticking
            else
            {
                ImGui::BeginDisabled();
                if(ImGui::Button("Play", ImVec2(100, 20)))
                {
                    World::GetInstance()->SetWorldTick(true);
                    World::GetInstance()->Init();
                }
                ImGui::EndDisabled();
            }
            
            ImGui::SameLine();
            if(ImGui::Button("Stop", ImVec2(100, 20)))
            {
                if(World::GetInstance()->GetWorldTick())
                {
                    World::GetInstance()->SetWorldTick(false);
                    World::GetInstance()->End();
                }
                
            }
            ImGui::Unindent(600);
            
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

        //ImGui performance window
        ImGui::Begin("Performance Window");
        ImGui::Text("DeltaTime: %f", deltaTime);
        ImGui::Text("Window width: %d", windowWidth);
        ImGui::Text("Window height: %d", windowHeight);
        ImGui::End();

        //Tick & Draw all active windows of the viewport
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

    //Clear all engine systems
    delete World::GetInstance();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}


