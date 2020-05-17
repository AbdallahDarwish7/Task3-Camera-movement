cmake_minimum_required(VERSION 3.15)
project(Humman_Body)
set(CMAKE_CXX_STANDARD 11)

find_package(OpenGL)
find_package(GLUT)

set(Files main.cpp imageLoader.h imageLoader.cpp bodyParts.h bodyParts.cpp )
add_executable(${CMAKE_PROJECT_NAME} ${Files})
target_link_libraries(${CMAKE_PROJECT_NAME}  ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLM_LIBRARY})