cmake_minimum_required(VERSION 3.0.0)

set(SRCS
  06_LinearQueue.cpp)

add_executable(06_LinearQueue
  ${SRCS})

set(LIBS
  PerformanceStatistics
  Utility)

target_link_libraries(06_LinearQueue
  ${LIBS})

add_dependencies(06_LinearQueue
  ${LIBS})