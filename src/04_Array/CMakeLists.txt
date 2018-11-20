cmake_minimum_required(VERSION 3.0.0)

set(SRCS
  04_Array.cpp)

add_executable(04_Array
  ${SRCS})

set(LIBS
  Utility)

target_link_libraries(04_Array
  ${LIBS})

add_dependencies(04_Array
  ${LIBS})