cmake_minimum_required(VERSION 3.0.0)

set(SRCS
  07_HashTable.cpp)

add_executable(07_HashTable
  ${SRCS})

set(LIBS
  PerformanceStatistics
  Utility)

target_link_libraries(07_HashTable
  ${LIBS})

add_dependencies(07_HashTable
  ${LIBS})