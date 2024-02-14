cmake_minimum_required(VERSION 3.10)
project(echo_server)

# Set the C++ standard (change as needed)
set(CMAKE_CXX_STANDARD 11)

add_executable(server server.cpp)
add_executable(client client.cpp)

target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
target_include_directories(client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

# target_link_libraries(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../)
# target_link_libraries(client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../ socket) 