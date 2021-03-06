#cmake -G "Visual Studio 15 2017 Win64" ..
cmake_minimum_required(VERSION 3.10)

project(main)

set(GLAD_PATH ${CMAKE_SOURCE_DIR}/3part_libs/glad)
set(GLFW_PATH ${CMAKE_SOURCE_DIR}/3part_libs/glfw3)
set(GL_PATH   ${CMAKE_SOURCE_DIR}/3part_libs/opengl)
set(GLM_PATH ${CMAKE_SOURCE_DIR}/3part_libs/glm)
find_library(LIBGLFW glfw3.lib ${GLFW_PATH}/lib)
find_library(LIBGL   opengl32.lib ${GL_PATH}/lib)

include_directories(include)
include_directories(${GLAD_PATH}/include)
include_directories(${GLFW_PATH}/include)
include_directories(${GLM_PATH}/include)

aux_source_directory(${GLAD_PATH}/src SRC_FILES)
aux_source_directory(src SRC_FILES)

add_executable(main ${SRC_FILES})

target_link_libraries(main ${LIBGLFW}
                           ${LIBGL})
