#include "GlUtils.h"
#include <iostream>

#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

int windowWidth = 1200, windowHeight = 940;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    if(width != 0 && height != 0)
    {
        windowWidth = width;
        windowHeight = height;
    }
}

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
    glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);

    //Init Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    //Init ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    io.Fonts->AddFontDefault();

    glEnable(GL_DEPTH_TEST); //Enable Depth testing
    glEnable(GL_SCISSOR_TEST);
   
    return true;
}
