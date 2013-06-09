cmake_minimum_required(VERSION 2.8)

######### Project Setup
project(RaytracerV3)

IF(NOT CMAKE_BUILD_TYPE)
#  SET(CMAKE_BUILD_TYPE "DEBUG")
  SET(CMAKE_BUILD_TYPE "RELEASE")
ENDIF()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules)

SET( CMAKE_C_COMPILER gcc-4.7)
SET( CMAKE_CXX_COMPILER g++-4.7)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLFW REQUIRED)

ADD_DEFINITIONS("-Wall -O3 -march=corei7-avx -std=c++0x -lglfw")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")



include_directories(
        RaytracerV3
        RaytracerV3/Core
        RaytracerV3/Core/Primitives
        RaytracerV3/Core/Primitives/Lights
        RaytracerV3/Core/Primitives/Shapes
        RaytracerV3/Core/Shaders
        RaytracerV3/Math
        ${OPENGL_INCLUDE_DIRS}
        ${GLUT_INCLUDE_DIRS} 
  )

file(GLOB SOURCES_MATH
        RaytracerV3/Math/*.cpp
        )
file(GLOB SOURCES_OGL
    RaytracerV3/OGL/*.cpp
    )
file(GLOB SOURCES_PLATFORM
    RaytracerV3/Platform/*.cpp
    )
file(GLOB SOURCES_CORE
    RaytracerV3/Core/*.cpp
    RaytracerV3/Core/Primitives/*.cpp
    RaytracerV3/Core/Primitives/Lights/*.cpp
    RaytracerV3/Core/Primitives/Shapes/*.cpp
    RaytracerV3/Core/Shaders/*.cpp
    )


set(SOURCES
    RaytracerV3/main.cpp
    RaytracerV3/PhotonMapper.cpp
    RaytracerV3/RenderGL.cpp
    RaytracerV3/SceneLoader.cpp
    RaytracerV3/Window.cpp
    )

add_executable(raytracerV3 ${SOURCES} ${SOURCES_MATH} ${SOURCES_OGL} ${SOURCES_PLATFORM} ${SOURCES_CORE})
target_link_libraries(raytracerV3 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLFW_LIBRARY})

