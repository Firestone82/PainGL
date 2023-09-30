#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <cstdio>

struct point {
    float pos[4];
    float color[4];
};

const point b[] = {
        { { -.5f, -.5f, .5f, 1 }, { 1, 0, 0, 1 } },
        { { -.5f, .5f, .5f, 1 }, { 0, 1, 0, 1 } },
        { { .5f, .5f, .5f, 1 }, { 0, 0, 1, 1 } },
        { { .5f, -.5f, .5f, 1 }, { 1, 1, 1, 1 } },
};

const char* vertex_shader =
        "#version 330\n"
        "layout(location=0) in vec4 position;"
        "layout(location=1) in vec4 vertex_Color;"
        "out vec4 colorInput;"
        "void main () {"
        "     gl_Position = position;"
        "     colorInput = vertex_Color;"
        "}";

const char* fragment_shader =
        "#version 330\n"
        "in vec4 colorInput;"
        "out vec4 color;"
        "void main () {"
        "     color = colorInput;"
        "}";

int main() {
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }

    GLFWwindow* window = glfwCreateWindow(600, 600, "ZPG", NULL, NULL);
    glfwSetWindowPos(window, 720, 480);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    //create and compile shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_shader, nullptr);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, fragmentShader);
    glAttachShader(shaderProgram, vertexShader);
    glLinkProgram(shaderProgram);

    //vertex buffer object (VBO)
    GLuint VBO = 0;
    glGenBuffers(1, &VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(b), b, GL_STATIC_DRAW);

    //Vertex Array Object (VAO)
    GLuint VAO = 0;
    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO
    glEnableVertexAttribArray(0); //enable vertex attributes
    glEnableVertexAttribArray(1); //enable vertex attributes
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(b[0]), (GLvoid*)0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(b[0]), (GLvoid*)(4*4));

//    GLint status;
//    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
//    if (status == GL_FALSE)
//    {
//        GLint infoLogLength;
//        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
//        GLchar* strInfoLog = new GLchar[infoLogLength + 1];
//        glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, strInfoLog);
//        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
//        delete[] strInfoLog;
//    }

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        glDrawArrays(GL_POLYGON, 0, 4); //mode,first,count

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    exit(EXIT_SUCCESS);
}


