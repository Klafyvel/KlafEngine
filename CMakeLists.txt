cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project(KlafEngine)

set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})
include_directories(include)

file(

	GLOB_RECURSE

	source_files

	src/*

	include/*

)

add_library(

	KlafEngine

	SHARED

	${source_files}

)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
target_link_libraries(KlafEngine ${SFML_LIBRARIES})

set_property(TARGET KlafEngine PROPERTY CXX_STANDARD 11)
set_property(TARGET KlafEngine PROPERTY CXX_STANDARD_REQUIRED ON)
