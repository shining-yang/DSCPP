cmake_minimum_required(VERSION 3.0.0)

set(SRCS
  04_Matrix.cpp)

add_executable(04_Matrix
  ${SRCS})

set(LIBS
  Utility)

target_link_libraries(04_Matrix
  ${LIBS})

add_dependencies(04_Matrix
  ${LIBS})