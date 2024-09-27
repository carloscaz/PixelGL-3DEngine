#pragma once
#include "../Dependencies/include/glad/glad.h"
#include "../Dependencies/include/GLFW/glfw3.h"

extern int windowWidth;
extern int windowHeight;

bool InitEngine(GLFWwindow*& _window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

namespace GLUtils
{
    void CreateLight();
    void CreateDirectionalLight();
    void CreatePointLight();
    void CreateSpotLight();
    void CreateCube();
    void CreateDemoMesh();
}
