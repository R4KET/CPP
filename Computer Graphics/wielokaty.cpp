#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

// Shader vertex
const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    void main()
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
)";

// Shader fragment
const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    void main()
    {
        FragColor = vec4(1.0, 0.0, 0.0, 1.0); // Kolor czerwony dla pierwszego pięciokąta
    }
)";

// Shader fragment dla drugiego pięciokąta
const char* fragmentShaderSource2 = R"(
    #version 330 core
    out vec4 FragColor;
    void main()
    {
        FragColor = vec4(0.0, 0.0, 1.0, 1.0); // Kolor niebieski dla drugiego pięciokąta
    }
)";

int main()
{
    // Inicjalizacja GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Tworzenie okna
    const unsigned int window_width = 1000;
    const unsigned int window_height = 800;
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "grafika komputerowa", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Inicjalizacja GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, (GLuint)window_width, (GLuint)window_height);

    // Kompilacja i linkowanie shaderów
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    unsigned int shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);
    glUseProgram(shaderProgram2);

    // Definicja wierzchołków pierwszego pięciokąta
    float vertices1[] = {
        // x, y, z
        -0.8f, -0.4f, 0.0f,
        -0.7f, 0.7f, 0.0f,
        -0.6f, 0.5f, 0.0f,
        -0.5f, -0.6f, 0.0f,
        -0.4f, -0.8f, 0.0f,
    };

    // Definicja wierzchołków drugiego pięciokąta
    float vertices2[] = {
        // x, y, z
        -0.2f, -0.2f, 0.0f,
        -0.5f, 0.6f, 0.0f,
        0.7f, 0.9f, 0.0f,
        0.2f, 0.0f, 0.0f,
        0.1f, -0.8f, 0.0f,
    };

    // Utworzenie i konfiguracja VAO (Vertex Array Object) oraz VBO (Vertex Buffer Object) dla pierwszego pięciokąta
    unsigned int VAO1, VBO1;
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO1);
    glBindVertexArray(VAO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Utworzenie i konfiguracja VAO oraz VBO dla drugiego pięciokąta
    unsigned int VAO2, VBO2;
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);
    glBindVertexArray(VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Pętla zdarzeń
    while (!glfwWindowShouldClose(window))
    {
        // Renderowanie
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Ustawienie koloru tła na czarny
        glClear(GL_COLOR_BUFFER_BIT);

        // Rysowanie pierwszego pięciokąta
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 5);

        // Rysowanie drugiego pięciokąta
        glUseProgram(shaderProgram2);
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 5);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO1);
    glDeleteBuffers(1, &VBO1);
    glDeleteVertexArrays(1, &VAO2);
    glDeleteBuffers(1, &VBO2);
    glDeleteProgram(shaderProgram);
    glDeleteProgram(shaderProgram2);

    glfwTerminate();
    return 0;
}
