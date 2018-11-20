cmake_minimum_required(VERSION 3.0.0)

set(SRCS
  08_BinaryTree.cpp)

add_executable(08_BinaryTree
  ${SRCS})

set(LIBS
  PerformanceStatistics
  Utility)

target_link_libraries(08_BinaryTree
  ${LIBS})

add_dependencies(08_BinaryTree
  ${LIBS})