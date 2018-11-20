cmake_minimum_required(VERSION 3.0.0)

set(SRCS
  05_StackLinkedList.cpp)

add_executable(05_StackLinkedList
  ${SRCS})

set(LIBS
  PerformanceStatistics
  Utility)

target_link_libraries(05_StackLinkedList
  ${LIBS})

add_dependencies(05_StackLinkedList
  ${LIBS})