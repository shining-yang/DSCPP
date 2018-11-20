cmake_minimum_required(VERSION 3.0.0)

set(SRCS
  09_PriorityQueue.cpp)

add_executable(09_PriorityQueue
  ${SRCS})

set(LIBS
  PerformanceStatistics
  Utility)

target_link_libraries(09_PriorityQueue
  ${LIBS})

add_dependencies(09_PriorityQueue
  ${LIBS})