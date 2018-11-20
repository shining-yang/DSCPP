cmake_minimum_required(VERSION 3.0.0)

set(SRCS
  10_WinnerTree.cpp)

add_executable(10_WinnerTree
  ${SRCS})

set(LIBS
  PerformanceStatistics
  Utility)

target_link_libraries(10_WinnerTree
  ${LIBS})

add_dependencies(10_WinnerTree
  ${LIBS})