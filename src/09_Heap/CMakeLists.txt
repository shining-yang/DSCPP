cmake_minimum_required(VERSION 3.0.0)

set(SRCS
  09_Heap.cpp)

add_executable(09_Heap
  ${SRCS})

set(LIBS
  PerformanceStatistics
  Utility)

target_link_libraries(09_Heap
  ${LIBS})

add_dependencies(09_Heap
  ${LIBS})