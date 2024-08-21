#include "GlUtils.h"
#include <iostream>

#include "Entities/Camera.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "World/World.h"

int windowWidth = 1500, windowHeight = 800;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    if(width != 0 && height != 0)
    {
        windowWidth = width;
        windowHeight = height;
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
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
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
    glEnable(GL_SCISSOR_TEST);

    glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
    // glfwSetCursorPosCallback(_window, mouse_callback);  
    //glfwSetMouseButtonCallback(_window, mouse_button_callback);
    
    return true;
}
