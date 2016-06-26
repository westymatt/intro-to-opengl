cmake_minimum_required(VERSION 2.8)
project(intro-to-opengl)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(INTRO_TO_OPENGL_SRCS
  ${PROJECT_SOURCE_DIR}/main.cpp
  ${PROJECT_SOURCE_DIR}/display.cpp
  ${PROJECT_SOURCE_DIR}/shader.cpp
  ${PROJECT_SOURCE_DIR}/mesh.cpp
)

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)

if (GLEW_FOUND)
    include_directories($(GLEW_INCLUDE_DIRS))
endif()
include_directories("/usr/local/include")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++1y -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -O1")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -v -framework OpenGL")


add_executable(
  intro-to-opengl
  ${INTRO_TO_OPENGL_SRCS}
)

target_link_libraries(intro-to-opengl ${SDL2_LIBRARY} ${GLEW_LIBRARIES})
file(COPY res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
