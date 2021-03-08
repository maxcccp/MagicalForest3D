cmake_minimum_required(VERSION 3.5)

# www.mbprogrammer.com
# Copyright © 2018-2019 Maxcccp 
message( STATUS "Copyright © 2018-2019 Maxcccp (www.mbprogrammer.com)" ) 

project(MF3D_Game)


message(STATUS ${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/dep)
include_directories(${CMAKE_SOURCE_DIR}/dep/lib64)
include_directories(${CMAKE_SOURCE_DIR}/dep/freetype2)

include_directories(${CMAKE_SOURCE_DIR}/engine)
include_directories(${CMAKE_SOURCE_DIR}/engine/core)
include_directories(${CMAKE_SOURCE_DIR}/engine/common)
include_directories(${CMAKE_SOURCE_DIR}/engine/core/window)
include_directories(${CMAKE_SOURCE_DIR}/engine/core/time)
include_directories(${CMAKE_SOURCE_DIR}/engine/core/texture)
include_directories(${CMAKE_SOURCE_DIR}/engine/core/shape)
include_directories(${CMAKE_SOURCE_DIR}/engine/core/shader)
include_directories(${CMAKE_SOURCE_DIR}/engine/core/script)
#include_directories(${CMAKE_SOURCE_DIR}/engine/core/physic)
include_directories(${CMAKE_SOURCE_DIR}/engine/core/particle)
include_directories(${CMAKE_SOURCE_DIR}/engine/core/model)
include_directories(${CMAKE_SOURCE_DIR}/engine/core/material)
include_directories(${CMAKE_SOURCE_DIR}/engine/core/font)
include_directories(${CMAKE_SOURCE_DIR}/engine/core/camera)
include_directories(${CMAKE_SOURCE_DIR}/engine/core/buffer)

link_directories(${CMAKE_SOURCE_DIR}/dep/lib64)

IF ( LINUX )
	IF( CMAKE_BUILD_TYPE STREQUAL "Debug" )
		add_definitions( "-O0 -g -Wall -std=c++11" )
	elseif( CMAKE_BUILD_TYPE STREQUAL "Release" )
		add_definitions( "-O2 -Wall -Werror -std=c++11" )
	endif( CMAKE_BUILD_TYPE STREQUAL "Debug" )

elseif( WIN32 )
		#add_definitions( -D_SCL_SECURE_NO_WARNINGS )
		add_definitions( -D_SRT_SECURE_NO_WARNINGS -D_STB_IMAGE_STATIC )
		#add_definitions( -D_WIN32_WINNT=0X5001 )

endif( LINUX )

# set( CMAKE_BUILD_TYPE Debug )
# set( CMAKE_BUILD_TYPE Release )

set( CMAKE_CXX_STANDART 11 )
# set( CMAKE_CXX_STANDART 14 )
# set( CMAKE_CXX_STANDART 17 )

# set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98" )
# set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++03" )
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
# set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14" )
# set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17" )
# set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y" )

set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W" )

# set( SOURCES ../main.cpp )
#or
file( GLOB_RECURSE SOURCE_FILES  "${CMAKE_SOURCE_DIR}/engine/*.c" "${CMAKE_SOURCE_DIR}/engine/*.cpp" )
file( GLOB_RECURSE HEADER_FILES  "${CMAKE_SOURCE_DIR}/engine/*.h" "${CMAKE_SOURCE_DIR}/engine/*.hpp" )
message( STATUS "${SOURCE_FILES}" )


# add_executable( ${PROJECT_NAME} maim.cpp )
# add_executable( ${PROJECT_NAME} ${SOURCES} )
add_executable( ${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} )

# We need a CMAKE_DIR with some code to find external dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")


# OpenGL
find_package(OpenGL REQUIRED)

# GLEW
INCLUDE(${CMAKE_SOURCE_DIR}/cmake/FindGLEW.cmake)

# SDL2
INCLUDE(${CMAKE_SOURCE_DIR}/cmake/FindGLFW3.cmake)

# ASSIMP
INCLUDE(${CMAKE_SOURCE_DIR}/cmake/FindASSIMP.cmake)