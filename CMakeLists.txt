cmake_minimum_required(VERSION 3.30)

project(sdl_template_cmake)

set(CMAKE_CXX_STANDARD 23)

add_compile_definitions(SHADER_DIR="${PROJECT_SOURCE_DIR}/shaders/")
add_compile_definitions(PROJECT_DIR="${PROJECT_SOURCE_DIR}/")

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug$<$<CONFIG:Debug>:Debug>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glew/build/cmake")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glad")

#add_library(SDL2 INTERFACE)
#target_include_directories(SDL2 INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/sdl2/include")

set(SDL2_DIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/sdl2/cmake")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(sdl_template_cmake main.cpp
        Mesh.cpp
        Shader.cpp
        Shader.h
        SDLWindow.cpp
        SDLWindow.h)

target_link_libraries(sdl_template_cmake PUBLIC
        glew
        ${SDL2_LIBRARIES}
        glad
)

target_include_directories(sdl_template_cmake PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glew/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glm"
        "${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glad/include"
)

link_directories("${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glew/lib")
link_directories("${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/sdl2/lib")