cmake_minimum_required(VERSION 3.30)

project(sdl_template_cmake)

set(CMAKE_CXX_STANDARD 23)

add_compile_definitions(SHADER_DIR="${PROJECT_SOURCE_DIR}/shaders/")
add_compile_definitions(PROJECT_DIR="${PROJECT_SOURCE_DIR}/")
add_compile_definitions(TEXTURE_DIR="${PROJECT_SOURCE_DIR}/textures/")

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug$<$<CONFIG:Debug>:Debug>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
#set(CMAKE_VERBOSE_MAKEFILE ON)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glad")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/soil")

set(SDL2_DIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/sdl2/cmake")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/thirdParty")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/soil/includes")

add_executable(sdl_template_cmake main.cpp
        Mesh.cpp
        Shader.cpp
        Shader.h
        SDLWindow.cpp
        SDLWindow.h
        Camera.cpp
        Camera.h
        Texture.cpp
        Texture.h
        thirdParty/stb/stb_image.h
        Light.cpp
        Light.h
        Material.cpp
        Material.h
        PointLight.cpp
        PointLight.h
)

target_link_libraries(sdl_template_cmake PUBLIC
        #glew
        ${SDL2_LIBRARIES}
        glad
        soil
)

target_include_directories(sdl_template_cmake PUBLIC
        #"${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glew/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glm"
        "${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glad/include"
        #"${CMAKE_CURRENT_SOURCE_DIR}/thirdParty"
)

#link_directories("${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glew/lib")
link_directories("${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/sdl2/lib")