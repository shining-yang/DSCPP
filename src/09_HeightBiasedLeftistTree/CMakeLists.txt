cmake_minimum_required(VERSION 3.0.0)

set(SRCS
  09_HeightBiasedLeftistTree.cpp)

add_executable(09_HeightBiasedLeftistTree
  ${SRCS})

set(LIBS
  PerformanceStatistics
  Utility)

target_link_libraries(09_HeightBiasedLeftistTree
  ${LIBS})

add_dependencies(09_HeightBiasedLeftistTree
  ${LIBS})