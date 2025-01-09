cmake_minimum_required(VERSION 3.30)

project(sdl_template_cmake)

set(CMAKE_CXX_STANDARD 23)


add_compile_definitions(SHADER_DIR="${PROJECT_SOURCE_DIR}/shaders/")
add_compile_definitions(PROJECT_DIR="${PROJECT_SOURCE_DIR}/")
add_compile_definitions(TEXTURE_DIR="${PROJECT_SOURCE_DIR}/textures/")
add_compile_definitions(SOURCE_DIR="${PROJECT_SOURCE_DIR}/src")

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug$<$<CONFIG:Debug>:Debug>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
#set(CMAKE_VERBOSE_MAKEFILE ON)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glad")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/soil")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/assimp")

set(SDL2_DIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/sdl2/cmake")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/thirdParty")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/soil/includes")
include_directories("${PROJECT_SOURCE_DIR}/src")

add_executable(sdl_template_cmake
        src/main.cpp
        src/Mesh.cpp
        src/Shader.cpp
        src/Shader.h
        src/SDLWindow.cpp
        src/SDLWindow.h
        src/Camera.cpp
        src/Camera.h
        src/Texture.cpp
        src/Texture.h
        src/light/Light.cpp
        src/light/Light.h
        src/Material.cpp
        src/Material.h
        src/light/PointLight.cpp
        src/light/PointLight.h
        src/ErrorReportingGPU.cpp
        src/ErrorReportingGPU.h
        src/light/SpotLight.cpp
        src/light/SpotLight.h
        src/Model.cpp
        src/Model.h
)

target_link_libraries(sdl_template_cmake PUBLIC
        #glew
        ${SDL2_LIBRARIES}
        glad
        soil
        assimp
)

target_include_directories(sdl_template_cmake PUBLIC
        #"${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glew/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glm"
        "${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glad/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/assimp/include"
        #"${CMAKE_CURRENT_SOURCE_DIR}/thirdParty"
)

#link_directories("${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glew/lib")
link_directories("${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/sdl2/lib")


