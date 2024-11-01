cmake_minimum_required(VERSION 3.5)

include_directories(../include)

set(projectName List)

project(${projectName}
	LANGUAGES CXX
)

add_library(
	Lists
	../include/Lists_errors.hpp
	../include/Lists_dump.hpp
	../include/Lists.hpp
	Lists_errors.cpp
	Lists_dump.cpp
	Lists.cpp
)

add_compile_definitions(LIST_CONSOLE_DUMP)

add_executable(${projectName} main.cpp)

target_link_libraries(${projectName} PRIVATE Lists)
