cmake_minimum_required(VERSION 3.0.0)

set(SRCS
  11_IndexedBinarySearchTree.cpp)

add_executable(11_IndexedBinarySearchTree
  ${SRCS})

set(LIBS
  PerformanceStatistics
  Utility)

target_link_libraries(11_IndexedBinarySearchTree
  ${LIBS})

add_dependencies(11_IndexedBinarySearchTree
  ${LIBS})