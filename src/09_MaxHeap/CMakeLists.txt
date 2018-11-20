cmake_minimum_required(VERSION 3.0.0)

set(SRCS
  09_MaxHeap.cpp)

add_executable(09_MaxHeap
  ${SRCS})

set(LIBS
  PerformanceStatistics
  Utility)

target_link_libraries(09_MaxHeap
  ${LIBS})

add_dependencies(09_MaxHeap
  ${LIBS})