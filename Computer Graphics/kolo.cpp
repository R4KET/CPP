#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <cmath>

using namespace std;


const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec2 position;
    void main()
    {
        gl_Position = vec4(position, 0.0, 1.0);
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    uniform vec3 color;
    void main()
    {
        FragColor = vec4(color, 1.0);
    }
)";

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    // inicjalizacja GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Tworzenie okna

    const unsigned int WINDOW_WIDTH = 800;
    const unsigned int WINDOW_HEIGHT = 800;
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Circle", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // inicjalizacja glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // tworzenme trojkatow
    int N;
    cout << "Podaj liczbe trojkatow (N >= 8): ";
    cin >> N;
    if (N < 8)
    {
        cout << "Wprowadzona wartosc jest mniejsza niz 8, generuje domyslne kolo zlozone z 8 trojkatow." << endl;
        N = 8;
    }

    const float radius = 0.5f;
    const float centerX = 0.0f;
    const float centerY = 0.0f;
    const float angleIncrement = 2 * 3.14159f / N;

    float* vertices = new float[N * 3 * 2];
    for (int i = 0; i < N; ++i)
    {
        float angle = i * angleIncrement;
        int baseIndex = i * 3 * 2;

        vertices[baseIndex] = centerX;
        vertices[baseIndex + 1] = centerY;

        vertices[baseIndex + 2] = centerX + radius * cos(angle);
        vertices[baseIndex + 3] = centerY + radius * sin(angle);

        vertices[baseIndex + 4] = centerX + radius * cos(angle + angleIncrement);
        vertices[baseIndex + 5] = centerY + radius * sin(angle + angleIncrement);
    }

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, N * 3 * 2 * sizeof(float), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // glowna petla zdarzen
    while (!glfwWindowShouldClose(window))
    {
        // renderowanie
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        int colorLoc = glGetUniformLocation(shaderProgram, "color");
        glUniform3f(colorLoc, 0.8f, 0.4f, 0.1f);

        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, N * 3);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete[] vertices;
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(shaderProgram);

    // ubij glfw
    glfwTerminate();

    return 0;
}
