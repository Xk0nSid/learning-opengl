#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

static unsigned int CompileShader(unsigned int shaderType, const std::string& source)
{
    unsigned int id = glCreateShader(shaderType);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // handle shader compilation error
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char message[length];
        // char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);

        std::cerr << "failed to compile "
                  << (shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment")
                  << " shader:" << std::endl
                  << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    int program_linked;
    glGetProgramiv(program, GL_LINK_STATUS, &program_linked);

    if (program_linked != GL_TRUE)
    {
        int log_length = 0;
        char message[1024];
        glGetProgramInfoLog(program, 1024, &log_length, message);
        std::cerr << "Failed to link shader program:" << std::endl
                  << message << std::endl;
        
        glDeleteShader(vs);
        glDeleteShader(fs);

        return 0;
    }

    glValidateProgram(program);

    int validate_status;
    glGetProgramiv(program, GL_VALIDATE_STATUS, &validate_status);

    if (validate_status == GL_FALSE) {
        int log_length = 0;
        char message[1024];
        glGetProgramInfoLog(program, 1024, &log_length, message);
        std::cerr << "Failed to validate shader program:" << std::endl
                  << message << std::endl;
        
        glDeleteShader(vs);
        glDeleteShader(fs);

        return 0;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main(int argc, char* argv[])
{
    (void) argc;
    (void) argv;

    std::cout << "Welcome to OpenGL tutorial" << std::endl;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize glfw" << std::endl;
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Learning", nullptr, nullptr);
    if (!window) {
        glfwTerminate();

        std::cerr << "Failed to create window" << std::endl;
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed initialize GLEW" << std::endl;

        glfwTerminate();
        return EXIT_FAILURE;
    }

    std::cout << "Using OpenGL " << glGetString(GL_VERSION) << std::endl;

    float positions[6] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    std::string vertexShader = R"glsl(
        #version 330 core
        layout(location = 0) in vec4 position;

        void main()
        {
           gl_Position = position;
        }
    )glsl";

    std::string fragShader = R"glsl(
        #version 330 core
        layout(location = 0) out vec4 color;

        void main()
        {
           color = vec4(1.0, 0.0, 0.0, 1.0);
        }
    )glsl";

    unsigned int shader = CreateShader(vertexShader, fragShader);
    glUseProgram(shader);

    while (!glfwWindowShouldClose(window)) {
        // Rendering Code Here

        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}