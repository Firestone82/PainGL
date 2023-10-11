cmake_minimum_required(VERSION 3.22.1)
project(ProjectZPG)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../target)

option(DISABLE_ASAN "Do not use Address sanitizer" OFF)

if(DISABLE_ASAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
endif()

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(assimp REQUIRED)

add_compile_options(
        -Wall
        -Wextra
        -pedantic
        -Wno-unused-parameter
        -Wno-unused-variable
        -Wno-unused-function
        -Wno-missing-field-initializers
)

add_executable(myApp
        src/main.cpp
        src/engine/Engine.cpp
        src/scene/window/Window.cpp
        src/scene/Scene.cpp
        src/listener/EventHandler.cpp
        src/buffer/VBO.cpp
        src/buffer/VAO.cpp
        src/buffer/EBO.cpp
        src/shader/shader/Shader.cpp
        src/shader/program/Program.cpp
        src/model/model/Model.cpp
        src/scene/entity/RenderableEntity.cpp
        src/shader/ShaderHandler.cpp
        src/model/ModelHandler.cpp
        src/logger/Logger.cpp
        src/gui/imgui/backend/imgui_impl_glfw.cpp
        src/gui/imgui/backend/imgui_impl_opengl3.cpp
        src/gui/imgui/imgui.cpp
        src/gui/imgui/imgui_widgets.cpp
        src/gui/imgui/imgui_tables.cpp
        src/gui/imgui/imgui_demo.cpp
        src/gui/imgui/imgui_draw.cpp
        src/gui/GUIHandler.cpp
        src/scene/camera/Camera.cpp
        src/scene/camera/Camera.h src/scene/transform/Transformation.cpp)

target_link_libraries(myApp glfw)
target_link_libraries(myApp OpenGL::GL)
target_link_libraries(myApp GLEW::GLEW)
target_link_libraries(myApp assimp::assimp)
