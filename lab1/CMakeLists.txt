 cmake_minimum_required(VERSION 3.0.0)
project(lab1)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab1 main.cpp Message.cpp Message.h DurationLogger.cpp DurationLogger.h MessageStore.cpp MessageStore.h)