cmake_minimum_required(VERSION 2.6)

project(Examples)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BUILD_TYPE})

include_directories(../include)

link_directories(/home/klafyvel/dev/KlafEngine/lib/${CMAKE_BUILD_TYPE})

add_executable(

	interface

	interface.cpp

)

target_link_libraries(

	interface

	KlafEngine

)
# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
target_link_libraries(interface ${SFML_LIBRARIES})

set_property(TARGET interface PROPERTY CXX_STANDARD 11)
set_property(TARGET interface PROPERTY CXX_STANDARD_REQUIRED ON)
