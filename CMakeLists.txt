cmake_minimum_required(VERSION 3.25)
project(ProjectZPG)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../target)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(assimp REQUIRED)

file(GLOB_RECURSE myApp_SRC "src/*.cpp" "include/*.cpp")
add_executable(myApp ${myApp_SRC})

target_include_directories(myApp PUBLIC include)

target_link_libraries(myApp glfw)
target_link_libraries(myApp OpenGL::GL)
target_link_libraries(myApp GLEW::GLEW)
target_link_libraries(myApp assimp::assimp)
