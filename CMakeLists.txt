cmake_minimum_required(VERSION 3.25)
project(assignment_2)

set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(solution2_3 submit/solution2_3.cpp)
add_executable(2_3 2_3.cpp BFPRT.hpp)
add_executable(2_4 2_4.cpp)
add_executable(BFPRT BFPRT_demo.cpp)

install(TARGETS 2_3
        RUNTIME DESTINATION bin
        COMPONENT 2_3)

install(TARGETS 2_4
        RUNTIME DESTINATION bin
        COMPONENT 2_4)

install(TARGETS BFPRT
       RUNTIME DESTINATION bin
       COMPONENT BFPRT)
add_executable(generate2_3 submit/generate2_3.cpp)
add_executable(solution2_4 submit/solution2_4.cpp)
add_executable(generate2_4 submit/generate2_4.cpp)
