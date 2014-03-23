cmake_minimum_required(VERSION 2.8)
project(raytracer)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_CXX_FLAGS "-g -std=c++11 -stdlib=libc++ -Wall -g -O0 -fms-extensions")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") 

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(CMAKE_CXX_FLAGS "-g -std=c++0x -pthread -Wall -g -O0 -fms-extensions")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

set(INCLUDE_DIRS "")
foreach(_headerFile ${HEADERS})
	get_filename_component(_dir ${_headerFile} PATH)
	list(APPEND INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

include_directories(${INCLUDE_DIRS})

add_executable(raytracer.out ${SOURCES})
