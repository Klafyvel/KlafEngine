cmake_minimum_required(VERSION 2.6)

project(Examples)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BUILD_TYPE})

include_directories(../include)

link_directories(/home/klafyvel/dev/KlafEngine/lib/${CMAKE_BUILD_TYPE})

add_executable(
	coreExample
	coreExample.cpp
)

add_executable(
	vectorExample
	vectorExample.cpp
)

add_executable(
	shapeExample
	shapeExample.cpp
)

target_link_libraries(
	coreExample
	KlafEngine
)
target_link_libraries(
	shapeExample
	KlafEngine
)
target_link_libraries(
	vectorExample
	KlafEngine
)
# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
target_link_libraries(coreExample ${SFML_LIBRARIES})
target_link_libraries(shapeExample ${SFML_LIBRARIES})

set_property(TARGET coreExample PROPERTY CXX_STANDARD 11)
set_property(TARGET coreExample PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET shapeExample PROPERTY CXX_STANDARD 11)
set_property(TARGET shapeExample PROPERTY CXX_STANDARD_REQUIRED ON)
