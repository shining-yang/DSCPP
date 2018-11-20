cmake_minimum_required(VERSION 3.0.0)

set(SRCS
  04_SparseMatrixLinked.cpp)

add_executable(04_SparseMatrixLinked
  ${SRCS})

set(LIBS
  PerformanceStatistics
  Utility)

target_link_libraries(04_SparseMatrixLinked
  ${LIBS})

add_dependencies(04_SparseMatrixLinked
  ${LIBS})