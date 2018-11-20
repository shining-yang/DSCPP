cmake_minimum_required(VERSION 3.0.0)

set(SRCS
  11_BinarySearchTree.cpp)

add_executable(11_BinarySearchTree
  ${SRCS})

set(LIBS
  PerformanceStatistics
  Utility)

target_link_libraries(11_BinarySearchTree
  ${LIBS})

add_dependencies(11_BinarySearchTree
  ${LIBS})