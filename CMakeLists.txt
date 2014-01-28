cmake_minimum_required(VERSION 2.8.5)

project(tapidoori)
find_package(SFML REQUIRED)

add_executable(server src/server.cpp)
add_executable(client src/client.cpp)

target_link_libraries(server sfml-network)
if(CMAKE_COMPILER_IS_GNUCXX)
	add_definitions(-std=c++11 -g3)
endif()
if(UNIX)
	target_link_libraries(client sfml-network sfml-graphics sfml-system sfml-window X11)
endif(UNIX)
if(WIN32)
	target_link_libraries(client sfml-network sfml-graphics sfml-system sfml-window)
endif(WIN32)
