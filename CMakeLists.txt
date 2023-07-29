cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 23)

project(lua-compiler VERSION 0.1)

# set up library
add_library(lua-compiler STATIC)
target_include_directories(lua-compiler PRIVATE
	include/lua-compiler
)
add_subdirectory(src)

# set up executable for manual testing
add_executable(lua-compiler-cli)
add_subdirectory(apps)

# set up test building
option(BUILD_TESTS "Build the tests" ON)
if (BUILD_TESTS)
	enable_testing()
	include(GoogleTest)
	add_subdirectory(test)
endif()

