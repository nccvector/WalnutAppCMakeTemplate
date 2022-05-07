cmake_minimum_required(VERSION 3.0)

project(walnutapp)

add_subdirectory(ext/GLFW)
add_subdirectory(ext/glm)

file(GLOB_RECURSE WALNUT_HDRS ext/Walnut/src/**.h)
file(GLOB_RECURSE WALNUT_SRCS ext/Walnut/src/**.cpp)

file(GLOB_RECURSE HDRS src/**.h)
file(GLOB_RECURSE SRCS src/**.cpp)

# Imgui sources
file(GLOB IMGUI_HDRS ext/imgui/*.h)
file(GLOB IMGUI_SRCS ext/imgui/*.cpp)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/ext/Walnut/src
    ${CMAKE_CURRENT_SOURCE_DIR}/ext/Walnut/src/Walnut
    ${CMAKE_CURRENT_SOURCE_DIR}/ext/Walnut/src/Walnut/ImGui
    ${CMAKE_CURRENT_SOURCE_DIR}/ext/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/ext/imgui/backends
    ${CMAKE_CURRENT_SOURCE_DIR}/ext/glfw/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ext/stb_image
    /usr/include/vulkan
    ${CMAKE_CURRENT_SOURCE_DIR}/ext/glm
)

find_package(Vulkan REQUIRED)

add_executable(${PROJECT_NAME}
    ${WALNUT_HDRS}
    ${WALNUT_SRCS}
    ${HRCS}
    ${SRCS}
    ${IMGUI_HDRS}
    ${IMGUI_SRCS}
)

target_link_libraries(${PROJECT_NAME}
    vulkan
    glfw
    glm
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)