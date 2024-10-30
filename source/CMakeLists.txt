cmake_minimum_required(VERSION 3.5)

set(projectName List)

project(${projectName}
	LANGUAGES CXX
)

include_directories(../include)

add_library(
	Lists
	../include/Lists_errors.hpp
	../include/List_dump.hpp
	../include/Lists.hpp
	Lists_errors.cpp
	Lists_dump.cpp
	Lists.cpp
)

add_executable(${projectName} main.cpp)

target_link_libraries(${projectName} PRIVATE Lists)
