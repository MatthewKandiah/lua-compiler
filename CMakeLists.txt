cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 23)

project(lua-compiler VERSION 0.1)

add_executable(lua-compiler)

target_include_directories(lua-compiler PRIVATE
	include/lua-compiler
)
add_subdirectory(src)

# set up test building
option(BUILD_TESTS "Build the tests" ON)
if (BUILD_TESTS)
	enable_testing()
	include(GoogleTest)
	add_subdirectory(test)
endif()

