#include "GlUtils.h"
#include <iostream>


#include "Buffers/Buffer.h"
#include "Components/Transform/TransformComponent.h"
#include "Entities/Camera.h"
#include "Entities/Lights/DirectionalLight.h"
#include "Entities/Lights/Light.h"
#include "Entities/Lights/PointLight.h"
#include "Entities/Lights/SpotLight.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "Material/Material.h"
#include "Mesh/Mesh.h"
#include "World/World.h"
#include "Shaders/Shader.h"
#include "Textures/Texture.h"
#include "Vertex/Vertex.h"

int windowWidth = 1920, windowHeight = 1009;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    if (width != 0 && height != 0)
    {
        windowWidth = width;
        windowHeight = height;
    }
}

namespace GLUtils
{
    static int lightIndex = 0;
    static int pointLightIndex = 0;
           std::vector<Vertex> vertices =
        {
            // Cara delantera
            Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f),
                   Vector3(0.0f, 0.0f, 1.0f)),
            Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f),
                   Vector3(0.0f, 0.0f, 1.0f)),
            Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f),
                   Vector3(0.0f, 0.0f, 1.0f)),
            Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f),
                   Vector3(0.0f, 0.0f, 1.0f)),

            // Cara trasera
            Vertex(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f),
                   Vector3(0.0f, 0.0f, -1.0f)),
            Vertex(Vector3(0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f),
                   Vector3(0.0f, 0.0f, -1.0f)),
            Vertex(Vector3(0.5f, 0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f),
                   Vector3(0.0f, 0.0f, -1.0f)),
            Vertex(Vector3(-0.5f, 0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f),
                   Vector3(0.0f, 0.0f, -1.0f)),

            // Cara izquierda
            Vertex(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f),
                   Vector3(-1.0f, 0.0f, 0.0f)),
            Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f),
                   Vector3(-1.0f, 0.0f, 0.0f)),
            Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f),
                   Vector3(-1.0f, 0.0f, 0.0f)),
            Vertex(Vector3(-0.5f, 0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f),
                   Vector3(-1.0f, 0.0f, 0.0f)),

            // Cara derecha
            Vertex(Vector3(0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f),
                   Vector3(1.0f, 0.0f, 0.0f)),
            Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f),
                   Vector3(1.0f, 0.0f, 0.0f)),
            Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f),
                   Vector3(1.0f, 0.0f, 0.0f)),
            Vertex(Vector3(0.5f, 0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f),
                   Vector3(1.0f, 0.0f, 0.0f)),

            // Cara superior
            Vertex(Vector3(-0.5f, 0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f),
                   Vector3(0.0f, 1.0f, 0.0f)),
            Vertex(Vector3(0.5f, 0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f),
                   Vector3(0.0f, 1.0f, 0.0f)),
            Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f),
                   Vector3(0.0f, 1.0f, 0.0f)),
            Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f),
                   Vector3(0.0f, 1.0f, 0.0f)),

            // Cara inferior
            Vertex(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f),
                   Vector3(0.0f, -1.0f, 0.0f)),
            Vertex(Vector3(0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f),
                   Vector3(0.0f, -1.0f, 0.0f)),
            Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f),
                   Vector3(0.0f, -1.0f, 0.0f)),
            Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f),
                   Vector3(0.0f, -1.0f, 0.0f))
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

    void CreateDirectionalLight()
    {
        Shader* shader = Shader::Load("Data/Shaders/LightSourceShader/VertexShader.glsl",
                                      "Data/Shaders/LightSourceShader/FragmentShader.glsl");
        std::string materialName = "Light Material";
        Material* material = new Material(shader, materialName, Vector3(1.0f, 1.0f, 1.0f));
        DirectionalLight* dirLight = new DirectionalLight(material);
        World::GetInstance()->SetDirectionalLight(dirLight);
        World::GetInstance()->AddEntity(dirLight);
    }

    void CreatePointLight()
    {
        Buffer* myBuffer = new Buffer(vertices, indices);


        Shader* lightSourceShader = Shader::Load("Data/Shaders/LightSourceShader/VertexShader.glsl",
                                                 "Data/Shaders/LightSourceShader/FragmentShader.glsl");
        std::string lightMaterialName = "Light Material";
        Material* lightMaterial = new Material(lightSourceShader, lightMaterialName,
                                               Vector3(1.0f, 1.0f, 1.0f));

           Mesh* mesh = new Mesh(lightMaterial, myBuffer);
        std::string lightName = std::string("PointLight" + std::to_string(pointLightIndex));
        PointLight* pointLight = new PointLight(lightName, mesh);
        ++pointLightIndex;
        pointLight->SetPosition(Vector3(0, 1, 0));
        pointLight->SetScale(Vector3(0.2f, 0.2f, 0.2f));
        World::GetInstance()->AddEntity(pointLight);
        World::GetInstance()->AddPointLight(pointLight);
    }

       static int spotLightIndex = 0;
    void CreateSpotLight()
    {


        Buffer* myBuffer = new Buffer(vertices, indices);


        Shader* lightSourceShader = Shader::Load("Data/Shaders/LightSourceShader/VertexShader.glsl",
                                                 "Data/Shaders/LightSourceShader/FragmentShader.glsl");
        std::string lightMaterialName = "Light Material";
        Material* lightMaterial = new Material(lightSourceShader, lightMaterialName,
                                               Vector3(1.0f, 1.0f, 1.0f));
           Mesh* mesh = new Mesh(lightMaterial, myBuffer);
        std::string lightName = std::string("SpotLight" + std::to_string(spotLightIndex));
        SpotLight* spotLight = new SpotLight(lightName, mesh);
        ++spotLightIndex;
        spotLight->SetPosition(Vector3(0, 1, 0));
        spotLight->SetScale(Vector3(0.2f, 0.2f, 0.2f));
        World::GetInstance()->AddEntity(spotLight);
        World::GetInstance()->AddSpotLight(spotLight);
    }

    static int cubeIndex = 0;

    void CreateCube()
    {
        Buffer* myBuffer = new Buffer(vertices, indices);

       
        Shader* shader = Shader::Load("Data/Shaders/lightShader/VertexShader.glsl",
                                      "Data/Shaders/lightShader/FragmentShader.glsl");
        std::string materialName = "Box Material";
        Material* material = new Material(shader, materialName, Vector3(1.0f, 1.0f, 1.0f),
                                          Vector3(1.0f, 1.0f, 1.0f));
        material->AddTexture(Texture::Load("Data/Textures/Box.png"));
        material->AddTexture(Texture::Load("Data/Textures/BoxSpecular.png"));
        material->AddTexture(Texture::Load("Data/Textures/matrix.jpg"));

           Mesh* mesh = new Mesh(material, myBuffer);
        Entity* cube = new Entity("Cube" + std::to_string(cubeIndex), mesh);
        ++cubeIndex;
           cube->SetIsSelectable(true);
        World::GetInstance()->AddEntity(cube);
    }

    void CreateDemoMesh()
    {
           std::vector<Mesh*> meshes = Mesh::Load("Data/Models/gunslinger.obj");
           std::string name = "Data/Models/gunslinger.obj";
           int init = name.find_last_of("/");
           int end = name.find_first_of(".");
           Entity* mesh = new Entity(name.substr(init + 1, end - init - 1), meshes);
           mesh->SetIsSelectable(true);
           mesh->GetComponent<TransformComponent>()->SetScale(Vector3(0.05f, 0.05f, 0.05f));
           World::GetInstance()->AddEntity(mesh);
    }
}


// void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
// {
//     if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
//         printf("HELLO\n");
// }

// void mouse_callback(GLFWwindow* window, double xPos, double yPos)
// {
//     if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
//     {
//         World::GetInstance()->GetActiveCamera()->UpdateDirection(xPos, yPos);
//     }
//   
// }

bool InitEngine(GLFWwindow*& _window) //Init all engine systems
{
    //Init & setup GLFW
    if (!glfwInit())
    {
        return false;
    }
    _window = glfwCreateWindow(windowWidth, windowHeight, "PixelGL", NULL, NULL);
    if (!_window)
    {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(_window);


    //Init Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    io.Fonts->AddFontDefault();

    glEnable(GL_DEPTH_TEST); //Enable Depth testing
    //glDepthFunc(GL_ALWAYS);
    //glEnable(GL_SCISSOR_TEST);

    glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
    // glfwSetCursorPosCallback(_window, mouse_callback);  
    //glfwSetMouseButtonCallback(_window, mouse_button_callback);

    return true;
}
