cmake_minimum_required(VERSION 3.5)
project(ean13)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_executable(${CMAKE_PROJECT_NAME} 
	src/main.cpp
	src/image/svg.cpp
	src/image/svg/rectangle.cpp
	src/image/svg/shape.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
	include
)
