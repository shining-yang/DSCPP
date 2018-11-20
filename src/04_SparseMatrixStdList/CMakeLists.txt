cmake_minimum_required(VERSION 3.0.0)

set(SRCS
  04_SparseMatrixStdList.cpp)

add_executable(04_SparseMatrixStdList
  ${SRCS})

set(LIBS
  PerformanceStatistics
  Utility)

target_link_libraries(04_SparseMatrixStdList
  ${LIBS})

add_dependencies(04_SparseMatrixStdList
  ${LIBS})