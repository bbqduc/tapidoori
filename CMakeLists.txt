cmake_minimum_required(VERSION 2.8.5)

project(tapidoori)
find_package(SFML REQUIRED)

add_executable(server src/server.cpp)
add_executable(client src/client.cpp)

target_link_libraries(server sfml-network)
target_link_libraries(client sfml-network)
