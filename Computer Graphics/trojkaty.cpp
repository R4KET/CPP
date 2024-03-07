#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cmath>


const GLchar* vertexShaderSource =
"#version 330 core\n"
"layout(location = 0) in vec3 position;\n"
"uniform mat4 model;\n"
"void main()\n"
"{\n"
"    gl_Position = model * vec4(position.x, position.y, position.z, 1.0);\n"
"}\n";

const GLchar* fragmentShaderSource1 =
"#version 330 core\n"
"out vec4 fragmentColor;\n"
"void main()\n"
"{\n"
"    fragmentColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
"}\n";

const GLchar* fragmentShaderSource2 =
"#version 330 core\n"
"out vec4 fragmentColor;\n"
"void main()\n"
"{\n"
"    fragmentColor = vec4(1.0, 1.0, 0.0, 1.0);\n"
"}\n";

const GLchar* fragmentShaderSource3 =
"#version 330 core\n"
"out vec4 fragmentColor;\n"
"void main()\n"
"{\n"
"    fragmentColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
"}\n";

const GLchar* fragmentShaderSource4 =
"#version 330 core\n"
"out vec4 fragmentColor;\n"
"void main()\n"
"{\n"
"    fragmentColor = vec4(0.0, 0.0, 1.0, 1.0);\n"
"}\n";


float vertices[] = {
    // coordinates
    -0.25f, -0.25f, 0.0f,
    0.25f, -0.25f, 0.0f,
    0.0f, 0.25f, 0.0f
};

int main()
{
    // inicjalizacja GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Tworzenie okna
    const unsigned int window_width = 800;
    const unsigned int window_height = 600;
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "grafika komputerowa", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // inicjalizacja GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Kompilacja shadera wierzchołków
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        char buffer[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
        std::cout << "Vertex shader compilation failed: " << buffer << std::endl;
    }

    // Kompilacja shadera fragmentów dla pierwszego trójkąta
    GLuint fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
    glCompileShader(fragmentShader1);

    glGetShaderiv(fragmentShader1, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        char buffer[512];
        glGetShaderInfoLog(fragmentShader1, 512, NULL, buffer);
        std::cout << "Fragment shader compilation failed: " << buffer << std::endl;
    }

    // Kompilacja shadera fragmentów dla drugiego trójkąta
    GLuint fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);

    glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        char buffer[512];
        glGetShaderInfoLog(fragmentShader2, 512, NULL, buffer);
        std::cout << "Fragment shader compilation failed: " << buffer << std::endl;
    }

    // Kompilacja shadera fragmentów dla trzeciego trójkąta
    GLuint fragmentShader3 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader3, 1, &fragmentShaderSource3, NULL);
    glCompileShader(fragmentShader3);

    glGetShaderiv(fragmentShader3, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        char buffer[512];
        glGetShaderInfoLog(fragmentShader3, 512, NULL, buffer);
        std::cout << "Fragment shader compilation failed: " << buffer << std::endl;
    }

    //Kompilacja shadera fragmentów dla czwartego trójkąta
    GLuint fragmentShader4 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader4, 1, &fragmentShaderSource4, NULL);
    glCompileShader(fragmentShader4);

    glGetShaderiv(fragmentShader4, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        char buffer[512];
        glGetShaderInfoLog(fragmentShader4, 512, NULL, buffer);
        std::cout << "Fragment shader compilation failed: " << buffer << std::endl;
    }


    // Linkowanie shaderów dla pierwszego trójkąta
    GLuint shaderProgram1 = glCreateProgram();
    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader1);
    glLinkProgram(shaderProgram1);

    glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &status);
    if (!status)
    {
        char buffer[512];
        glGetProgramInfoLog(shaderProgram1, 512, NULL, buffer);
        std::cout << "Shader program linking failed: " << buffer << std::endl;
    }

    // Linkowanie shaderów dla drugiego trójkąta
    GLuint shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);

    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &status);
    if (!status)
    {
        char buffer[512];
        glGetProgramInfoLog(shaderProgram2, 512, NULL, buffer);
        std::cout << "Shader program linking failed: " << buffer << std::endl;
    }

    // Linkowanie shaderów dla trzeciego trójkąta
    GLuint shaderProgram3 = glCreateProgram();
    glAttachShader(shaderProgram3, vertexShader);
    glAttachShader(shaderProgram3, fragmentShader3);
    glLinkProgram(shaderProgram3);

    glGetProgramiv(shaderProgram3, GL_LINK_STATUS, &status);
    if (!status)
    {
        char buffer[512];
        glGetProgramInfoLog(shaderProgram3, 512, NULL, buffer);
        std::cout << "Shader program linking failed: " << buffer << std::endl;
    }

    

    //Linkowanie shaderów dla czwartego trójkąta
    GLuint shaderProgram4 = glCreateProgram();
    glAttachShader(shaderProgram4, vertexShader);
    glAttachShader(shaderProgram4, fragmentShader4);
    glLinkProgram(shaderProgram4);

    glGetProgramiv(shaderProgram4, GL_LINK_STATUS, &status);
    if (!status)
    {
        char buffer[512];
        glGetProgramInfoLog(shaderProgram4, 512, NULL, buffer);
        std::cout << "Shader program linking failed: " << buffer << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader1);
    glDeleteShader(fragmentShader2);
    glDeleteShader(fragmentShader3);
    glDeleteShader(fragmentShader4);


    // Tworzenie i konfiguracja VAO i VBO dla pierwszego trójkąta
    GLuint VAO1, VBO1;
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO1);

    glBindVertexArray(VAO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Tworzenie i konfiguracja VAO i VBO dla drugiego trójkąta
    GLuint VAO2, VBO2;
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);

    glBindVertexArray(VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Tworzenie i konfiguracja VAO i VBO dla trzeciego trójkąta
    GLuint VAO3, VBO3;
    glGenVertexArrays(1, &VAO3);
    glGenBuffers(1, &VBO3);

    glBindVertexArray(VAO3);
    glBindBuffer(GL_ARRAY_BUFFER, VBO3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //Tworzenie i konfiguracja VAO i VBO dla czwartego trójkąta
    GLuint VAO4, VBO4;
    glGenVertexArrays(1, &VAO4);
    glGenBuffers(1, &VBO4);

    glBindVertexArray(VAO4);
    glBindBuffer(GL_ARRAY_BUFFER, VBO4);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // Początkowe wartości dla transformacji pierwszego trójkąta
    float x1 = -0.25f;
    float y1 = 0.25f;
    bool reverse1 = false;

    // Początkowe wartości dla transformacji drugiego trójkąta
    float angle2 = 0.0f;

    // Początkowe wartości dla transformacji trzeciego trójkąta
    float scale3 = 0.5f;
    bool growing3 = true;

    // Początkowe wartości dla transformacji czwartego trójkąta
    float angle4 = 0.0f;
    float scale4 = 0.5f;
    bool growing4 = true;
    float x4 = -0.75f;
    float y4 = -0.75f;
    bool reverse4 = false;

    // Główna pętla programu
    while (!glfwWindowShouldClose(window))
    {
        // Sprawdzenie i obsługa zdarzeń okna
        glfwPollEvents();

        // Renderowanie
        glClearColor(0.066f, 0.09f, 0.07f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Aktualizacja transformacji pierwszego trójkąta
        if (!reverse1)
        {
            x1 += 0.001f;
            y1 -= 0.001f;
            if (x1 >= -0.5f && y1 <= 0.5f)
            {
                reverse1 = true;
            }
        }
        else
        {
            x1 -= 0.001f;
            y1 += 0.001f;
            if (x1 <= -0.8f && y1 >= 0.8f)
            {
                reverse1 = false;
            }
        }

        glm::mat4 model1 = glm::mat4(1.0f);
        model1 = glm::translate(model1, glm::vec3(x1, y1, 0.0f));
        model1 = glm::scale(model1, glm::vec3(0.5f));

        // Ustawianie macierzy modelu pierwszego trójkąta w shaderze
        glUseProgram(shaderProgram1);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram1, "model"), 1, GL_FALSE, glm::value_ptr(model1));

        // Renderowanie pierwszego trójkąta
        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Aktualizacja transformacji drugiego trójkąta
        angle2 += 0.001f;
        glm::mat4 model2 = glm::mat4(1.0f);
        model2 = glm::translate(model2, glm::vec3(0.75f, 0.75f, 0.0f));
        model2 = glm::rotate(model2, angle2, glm::vec3(0.0f, 0.0f, 1.0f));
        model2 = glm::scale(model2, glm::vec3(0.5f));

        // Ustawianie macierzy modelu drugiego trójkąta w shaderze
        glUseProgram(shaderProgram2);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram2, "model"), 1, GL_FALSE, glm::value_ptr(model2));

        // Renderowanie drugiego trójkąta
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Aktualizacja transformacji trzeciego trójkąta
        if (growing3)
        {
            scale3 += 0.001f;
            if (scale3 >= 0.5f)
            {
                growing3 = false;
            }
        }
        else
        {
            scale3 -= 0.001f;
            if (scale3 <= 0.1f)
            {
                growing3 = true;
            }
        }

        glm::mat4 model3 = glm::mat4(1.0f);
        model3 = glm::translate(model3, glm::vec3(0.75f, -0.75f, 0.0f));
        model3 = glm::scale(model3, glm::vec3(scale3));

        // Ustawianie macierzy modelu trzeciego trójkąta w shaderze
        glUseProgram(shaderProgram3);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram3, "model"), 1, GL_FALSE, glm::value_ptr(model3));

        // Renderowanie trzeciego trójkąta
        glBindVertexArray(VAO3);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Aktualizacja transformacji czwartego trójkąta
        if (!reverse4)
        {
            x4 += 0.001f;
            y4 += 0.001f;
            if (x4 >= -0.25f && y4 >= -0.25f)
            {
                reverse4 = true;
            }
        }
        else
        {
            x4 -= 0.001f;
            y4 -= 0.001f;
            if (x4 <= -0.75f && y4 <= -0.75f)
            {
                reverse4 = false;
            }
        }

        angle4 += 0.001f;

        if (growing4)
        {
            scale4 += 0.001f;
            if (scale4 >= 0.5f)
            {
                growing4 = false;
            }
        }
        else
        {
            scale4 -= 0.001f;
            if (scale4 <= 0.1f)
            {
                growing4 = true;
            }
        }

        glm::mat4 model4 = glm::mat4(1.0f);
        model4 = glm::translate(model4, glm::vec3(x4, y4, 0.0f));
        model4 = glm::rotate(model4, angle4, glm::vec3(0.0f, 0.0f, 1.0f));
        model4 = glm::scale(model4, glm::vec3(scale4));

        // Ustawianie macierzy modelu czwartego trójkąta w shaderze
        glUseProgram(shaderProgram4);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram4, "model"), 1, GL_FALSE, glm::value_ptr(model4));

        // Renderowanie czwartego trójkąta
        glBindVertexArray(VAO4);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Zamiana buforów i synchronizacja
        glfwSwapBuffers(window);
    }

    // Usuwanie zasobów
    glDeleteVertexArrays(1, &VAO1);
    glDeleteBuffers(1, &VBO1);
    glDeleteVertexArrays(1, &VAO2);
    glDeleteBuffers(1, &VBO2);
    glDeleteVertexArrays(1, &VAO3);
    glDeleteBuffers(1, &VBO3);
    glDeleteVertexArrays(1, &VAO4);
    glDeleteBuffers(1, &VBO4);
    glDeleteProgram(shaderProgram1);
    glDeleteProgram(shaderProgram2);
    glDeleteProgram(shaderProgram3);
    glDeleteProgram(shaderProgram4);

    // Zamykanie okna GLFW i czyszczenie zasobów
    glfwTerminate();

    return 0;
}