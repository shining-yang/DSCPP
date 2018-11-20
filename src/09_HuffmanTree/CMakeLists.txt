cmake_minimum_required(VERSION 3.0.0)

set(SRCS
  09_HuffmanTree.cpp)

add_executable(09_HuffmanTree
  ${SRCS})

set(LIBS
  PerformanceStatistics
  Utility)

target_link_libraries(09_HuffmanTree
  ${LIBS})

add_dependencies(09_HuffmanTree
  ${LIBS})