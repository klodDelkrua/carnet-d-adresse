cmake_minimum_required(VERSION 3.10)
project(carnet_d_adress)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)

file(GLOB SOURCES "src/*.c")

add_executable(carnet_d_adress ${SOURCES})
