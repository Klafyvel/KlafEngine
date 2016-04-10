cmake_minimum_required(VERSION 2.6)

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
