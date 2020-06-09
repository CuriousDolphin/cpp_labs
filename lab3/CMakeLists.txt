cmake_minimum_required(VERSION 3.15)
project(lab3)

set(CMAKE_CXX_STANDARD 20)



add_executable(lab3 main.cpp Result.h MapperInput.h ReducerInput.h DurationLogger.cpp DurationLogger.h map_reduce.cpp map_reduce_regex.cpp map_reduce_forked.h)


find_package(Boost 1.67.0 COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(lab3 ${Boost_LIBRARIES})