cmake_minimum_required(VERSION 3.0.0)

set(SRCS
  01_Fibonacci.cpp)

add_executable(01_Fibonacci
  ${SRCS})

set(LIBS
  PerformanceStatistics)

target_link_libraries(01_Fibonacci
  ${LIBS})

add_dependencies(01_Fibonacci
  ${LIBS})