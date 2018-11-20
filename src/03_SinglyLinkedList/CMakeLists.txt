cmake_minimum_required(VERSION 3.0.0)

set(SRCS
  03_SinglyLinkedList.cpp)

add_executable(03_SinglyLinkedList
  ${SRCS})

set(LIBS
  PerformanceStatistics
  Utility)

target_link_libraries(03_SinglyLinkedList
  ${LIBS})

add_dependencies(03_SinglyLinkedList
  ${LIBS})