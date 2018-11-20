cmake_minimum_required(VERSION 3.0.0)

set(SRCS
  07_SortedList.cpp)

add_executable(07_SortedList
  ${SRCS})

set(LIBS
  PerformanceStatistics
  Utility)

target_link_libraries(07_SortedList
  ${LIBS})

add_dependencies(07_SortedList
  ${LIBS})