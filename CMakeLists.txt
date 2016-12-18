cmake_minimum_required(VERSION 2.8.9)
project(influenza)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

file(GLOB SOURCES "src/*.cpp" "src/utilities/*.cpp")

include_directories(include)

find_package(Boost COMPONENTS program_options REQUIRED)

add_executable(influenza ${SOURCES} include/instance.h include/config.h
        include/utilities/random_machine.h include/utilities/vector_operations.h include/utilities/common.h src/utilities/common.cpp)
target_link_libraries(influenza ${Boost_PROGRAM_OPTIONS_LIBRARIES})