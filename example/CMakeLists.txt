cmake_minimum_required(VERSION 2.6)

project(Examples)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BUILD_TYPE})

include_directories(../include)

link_directories(../lib/${CMAKE_BUILD_TYPE})

add_executable(

	interface

	interface.cpp

)

target_link_libraries(

	interface

	KlafEngine

)
