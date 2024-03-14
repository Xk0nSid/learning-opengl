#include <iostream>

#include <GLFW/glfw3.h>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

int main(int argc, char* argv[])
{
    (void) argc;
    (void) argv;

    std::cout << "Welcome to OpenGL tutorial" << std::endl;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize glfw" << std::endl;
        return EXIT_FAILURE;
    }

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Learning", nullptr, nullptr);
    if (!window) {
        glfwTerminate();

        std::cerr << "Failed to create window" << std::endl;
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        // Rendering Code Here

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}