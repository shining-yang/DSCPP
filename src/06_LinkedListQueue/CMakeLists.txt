cmake_minimum_required(VERSION 3.0.0)

set(SRCS
  06_LinkedListQueue.cpp)

add_executable(06_LinkedListQueue
  ${SRCS})

set(LIBS
  PerformanceStatistics
  Utility)

target_link_libraries(06_LinkedListQueue
  ${LIBS})

add_dependencies(06_LinkedListQueue
  ${LIBS})