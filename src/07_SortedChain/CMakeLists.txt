cmake_minimum_required(VERSION 3.0.0)

set(SRCS
  07_SortedChain.cpp)

add_executable(07_SortedChain
  ${SRCS})

set(LIBS
  PerformanceStatistics
  Utility)

target_link_libraries(07_SortedChain
  ${LIBS})

add_dependencies(07_SortedChain
  ${LIBS})