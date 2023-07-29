cmake_minimum_required(VERSION 3.19)

project(lua-compiler VERSION 0.1)

add_executable(lua-compiler)

target_include_directories(lua-compiler PRIVATE
	include/lua-compiler
)
add_subdirectory(src)

# set up test building
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	include(CTest)
endif()
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
	add_subdirectory(test)
endif()

