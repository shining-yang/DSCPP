cmake_minimum_required(VERSION 3.0.0)

set(SRCS
  07_SkipList.cpp)

add_executable(07_SkipList
  ${SRCS})

set(LIBS
  PerformanceStatistics
  Utility)

target_link_libraries(07_SkipList
  ${LIBS})

add_dependencies(07_SkipList
  ${LIBS})