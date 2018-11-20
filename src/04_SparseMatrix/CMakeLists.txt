cmake_minimum_required(VERSION 3.0.0)

set(SRCS
  04_SparseMatrix.cpp)

add_executable(04_SparseMatrix
  ${SRCS})

set(LIBS
  PerformanceStatistics
  Utility)

target_link_libraries(04_SparseMatrix
  ${LIBS})

add_dependencies(04_SparseMatrix
  ${LIBS})