#include "GL/glew.h"
#include "Program.h"

Program::Program() {
    this->program = glCreateProgram();
}

Program::~Program() {
    for (auto shader: this->shaders) {
        glDetachShader(this->program, shader->get());
        this->shaders.pop_back();
    }

    glDeleteProgram(this->program);
}

void Program::attach(Shader* shader) {
    this->shaders.push_back(shader);
    glAttachShader(this->program, shader->get());
}

void Program::setShaderVariableMatrix(const glm::mat4 &matrix, const std::string &variable) {
    GLint projectionMatrixLocation = glGetUniformLocation(this->program, variable.c_str());
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Program::link() {
    glLinkProgram(this->program);

    GLint status;
    glGetProgramiv(this->program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &infoLogLength);

        auto *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(this->program, infoLogLength, nullptr, strInfoLog);

        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    }
}

void Program::use() {
    glUseProgram(this->program);
}

GLuint Program::get() const {
    return this->program;
}