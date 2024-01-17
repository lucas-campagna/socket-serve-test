cmake_minimum_required(VERSION 3.10)
project(TCPEchoServer)

# Set the C++ standard (change as needed)
set(CMAKE_CXX_STANDARD 11)

# Add all .cpp files in the current directory to the executable
file(GLOB SOURCES "*.cpp")

add_executable(server ${SOURCES})
