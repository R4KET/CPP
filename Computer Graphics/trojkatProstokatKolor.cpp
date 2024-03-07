#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>
#include <iostream>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

float scroll_color = 0.0f;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec2 aTexCoord;\n"
"out vec2 TexCoord;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
"}\n\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec2 TexCoord;\n"
"uniform sampler2D texture1;\n"
"uniform float color;\n"
"void main()\n"
"{\n"
"   vec4 texColor = texture(texture1, TexCoord);\n"
"   vec4 tintedColor = vec4(color, color, color, 1.0);\n" //kolor scrolla
"   FragColor = texColor * tintedColor;\n"
"}\n\0";


float triangleVertices[] = {
    -1.0f, -0.5f, 0.0f, 0.0f, 0.0f,
    0.0f, -0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, 0.0f, 0.5f, 1.0f
};

float rectangleVertices[] = {
    0.75f, -0.25f, 0.0f, 1.0f, 0.0f,
    0.75f,  0.25f, 0.0f, 1.0f, 1.0f,
    0.25f,  0.25f, 0.0f, 0.0f, 1.0f,
    0.25f, -0.25f, 0.0f, 0.0f, 0.0f
};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};

bool triangle = false, rectangle = false;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        triangle = true;
        rectangle = false;
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        triangle = false;
        rectangle = true;
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        triangle = true;
        rectangle = true;
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    scroll_color += yoffset / 10;
    if (scroll_color > 1.0f)
        scroll_color = 1.0f;
    if (scroll_color < 0.0f)
        scroll_color = 0.0f;
}

int createTexture(const char* filename)
{
    int width, height, nrChannels;
    unsigned int texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (data)
    {
        GLenum format = (nrChannels == 3) ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Failed to load texture: " << filename << std::endl;
    }

    return texture;
}

unsigned int createVAO(float* vertices, int size)
{
    unsigned int VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return VAO;
}

int main()
{
    // Inicjalizacja GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Tworzenie okna GLFW
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "My Window", nullptr, nullptr);
    if (window == nullptr)
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

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetScrollCallback(window, scroll_callback);

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    unsigned int VAO1 = createVAO(triangleVertices, sizeof(triangleVertices));
    unsigned int VAO2 = createVAO(rectangleVertices, sizeof(rectangleVertices));
    unsigned int texture1 = createTexture("first.png");
    unsigned int texture2 = createTexture("second.png");


    //glowna petla zdarzen
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(1.0f, 0.92f, 0.23f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glUniform1f(glGetUniformLocation(shaderProgram, "color"), scroll_color);

        if (triangle)
        {
            glBindTexture(GL_TEXTURE_2D, texture1);
            glBindVertexArray(VAO1);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        if (rectangle)
        {
            glBindTexture(GL_TEXTURE_2D, texture2);
            glBindVertexArray(VAO2);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // czyszczenie
    glDeleteVertexArrays(1, &VAO1);
    glDeleteVertexArrays(1, &VAO2);
    glDeleteProgram(shaderProgram);


    //ubij glfw
    glfwTerminate();
    return 0;
}
