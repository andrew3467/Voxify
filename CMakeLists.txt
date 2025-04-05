cmake_minimum_required(VERSION 3.29)
project(Voxify)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(External)


file(GLOB_RECURSE SRC src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.h)

add_executable(
        Voxify
        ${SRC}
        ${HEADERS}
)

target_include_directories(
        Voxify
        PRIVATE
        src/Voxify
        External/stb
        PUBLIC
        External/imgui
)

target_link_libraries(
        Voxify
        PUBLIC
        spdlog::spdlog
        ImGui
        PRIVATE
        glad
        glfw
        glm::glm
        stb
)

target_precompile_headers(
        Voxify
        PUBLIC
        src/Voxify/voxifypch.h
)

target_compile_definitions(
        Voxify
        PRIVATE

        GLFW_INCLUDE_NONE
)
