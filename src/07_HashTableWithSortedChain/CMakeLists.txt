cmake_minimum_required(VERSION 3.0.0)

set(SRCS
  07_HashTableWithSortedChain.cpp)

add_executable(07_HashTableWithSortedChain
  ${SRCS})

set(LIBS
  PerformanceStatistics
  Utility)

target_link_libraries(07_HashTableWithSortedChain
  ${LIBS})

add_dependencies(07_HashTableWithSortedChain
  ${LIBS})