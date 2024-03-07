#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

const GLchar* vertexShaderSource =
"#version 330 core\n"
"layout(location = 0) in vec3 position;\n"
"layout(location = 1) in vec2 texCoord;\n"
"layout(location = 2) in vec3 normal;\n"
"out vec2 textureCoord;\n"
"out vec3 FragPos;\n"
"out vec3 Normal;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"    gl_Position = projection * view * model * vec4(position, 1.0);\n"
"    textureCoord = texCoord;\n"
"    FragPos = vec3(model * vec4(position, 1.0));\n"
"    Normal = mat3(transpose(inverse(model))) * normal;\n"
"}\n\0";

const GLchar* fragmentShaderSource =
"#version 330 core\n"
"in vec2 textureCoord;\n"
"in vec3 FragPos;\n"
"in vec3 Normal;\n"
"out vec4 fragmentColor;\n"
"uniform sampler2D textureSampler;\n"
"uniform vec3 lightPos;\n"
"uniform vec3 lightColor;\n"
"uniform vec3 objectColor;\n"
"uniform int useAmbient = 1;\n"
"uniform int useDiffuse = 1;\n"
"uniform int useSpecular = 1;\n"
"void main()\n"
"{\n"
"    vec3 ambient = vec3(0.1, 0.1, 0.1);\n"
"    vec3 norm = normalize(Normal);\n"
"    vec3 lightDir = normalize(lightPos - FragPos);\n"
"    float diff = max(dot(norm, lightDir), 0.0);\n"
"    vec3 diffuse = lightColor * diff * objectColor;\n"
"    vec3 viewDir = normalize(-FragPos);\n"
"    vec3 reflectDir = reflect(-lightDir, norm);\n"
"    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);\n"
"    vec3 specular = vec3(1.0) * spec;\n"
"    vec4 texColor = texture(textureSampler, textureCoord);\n"
"    vec3 result = vec3(0.0);\n"
"    if (useAmbient == 1)\n"
"        result += ambient;\n"
"    if (useDiffuse == 1)\n"
"        result += diffuse;\n"
"    if (useSpecular == 1)\n"
"        result += specular;\n"
"    fragmentColor = vec4(result * texColor.rgb, 1.0);\n"
"}\n\0";

GLfloat cubeVertices[] = {
    // Front face
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f,   1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f,    1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f,    1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f,   0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,

    // Back face
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
    0.5f, 0.5f, -0.5f,   1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
    0.5f, 0.5f, -0.5f,   1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
    -0.5f, 0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f,

    // Left face
    -0.5f, 0.5f, 0.5f,   0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f,  1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f,   0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,

    // Right face
    0.5f, 0.5f, 0.5f,    0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, -0.5f,   1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f,   0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f,    0.0f, 1.0f,  1.0f, 0.0f, 0.0f,

    // Top face
    -0.5f, 0.5f, 0.5f,   0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f,    1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f,   1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f,   1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f,   0.0f, 1.0f,  0.0f, 1.0f, 0.0f,

    // Bottom face
    -0.5f, -0.5f, 0.5f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, 0.5f,   1.0f, 1.0f,  0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f
};

int windowWidth = 800;
int windowHeight = 600;
float cameraSpeed = 3.0f;
float sensitivity = 0.1f;
float pitch = 0.0f;
float yaw = -90.0f;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec3 cameraPosition(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float lastX = windowWidth / 2.0f;
float lastY = windowHeight / 2.0f;

bool useAmbient = true;
bool useDiffuse = true;
bool useSpecular = true;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    windowWidth = width;
    windowHeight = height;
}

void processInput(GLFWwindow* window)
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    float cameraSpeedMultiplier = cameraSpeed * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPosition += cameraSpeedMultiplier * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPosition -= cameraSpeedMultiplier * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeedMultiplier;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeedMultiplier;

    // Toggle Ambient Light
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        useAmbient = !useAmbient;

    // Toggle Diffuse Light
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        useDiffuse = !useDiffuse;

    // Toggle Specular Light
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        useSpecular = !useSpecular;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

void calculateFPS(GLFWwindow* window)
{
    static double previousTime = glfwGetTime();
    static int frameCount = 0;

    double currentTime = glfwGetTime();
    double deltaTime = currentTime - previousTime;
    frameCount++;

    if (deltaTime >= 1.0)
    {
        double fps = static_cast<double>(frameCount) / deltaTime;
        double frameTime = 1000.0 / fps;

        std::ostringstream ss;
        ss << "My Window | FPS: " << fps << " | Frame Time: " << frameTime << "ms";
        std::string windowTitle = ss.str();
        glfwSetWindowTitle(window, windowTitle.c_str());

        frameCount = 0;
        previousTime = currentTime;
    }
}

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Nie uda³o siê zainicjowaæ GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "My Window", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Nie uda³o siê utworzyæ okna GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Nie uda³o siê zainicjowaæ GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, windowWidth, windowHeight);
    glEnable(GL_DEPTH_TEST);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        char error_message[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, error_message);
        std::cout << "B³¹d (Shader wierzcho³ków): " << error_message << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        char error_message[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, error_message);
        std::cout << "B³¹d (Shader fragmentów): " << error_message << std::endl;
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if (!status)
    {
        char error_message[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, error_message);
        std::cout << "B³¹d (Program shaderów): " << error_message << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* image = stbi_load("first.png", &width, &height, &channels, 0);
    if (image)
    {
        GLenum format;
        if (channels == 1)
            format = GL_RED;
        else if (channels == 3)
            format = GL_RGB;
        else if (channels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Nie uda³o siê za³adowaæ tekstury" << std::endl;
    }
    stbi_image_free(image);

    glm::vec3 objectColor(1.0f, 0.5f, 0.31f);
    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        calculateFPS(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

        glm::mat4 model;
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));

        GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        GLint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        GLint objectColorLoc = glGetUniformLocation(shaderProgram, "objectColor");
        glUniform3fv(objectColorLoc, 1, glm::value_ptr(objectColor));

        GLint lightColorLoc = glGetUniformLocation(shaderProgram, "lightColor");
        glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));

        GLint lightPosLoc = glGetUniformLocation(shaderProgram, "lightPos");
        glUniform3f(lightPosLoc, 1.2f, 1.0f, 2.0f);

        GLint useAmbientLoc = glGetUniformLocation(shaderProgram, "useAmbient");
        glUniform1i(useAmbientLoc, useAmbient);

        GLint useDiffuseLoc = glGetUniformLocation(shaderProgram, "useDiffuse");
        glUniform1i(useDiffuseLoc, useDiffuse);

        GLint useSpecularLoc = glGetUniformLocation(shaderProgram, "useSpecular");
        glUniform1i(useSpecularLoc, useSpecular);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}
