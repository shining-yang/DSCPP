cmake_minimum_required(VERSION 3.0.0)

set(SRCS
  05_StackLinearList.cpp)

add_executable(05_StackLinearList
  ${SRCS})

set(LIBS
  PerformanceStatistics
  Utility)

target_link_libraries(05_StackLinearList
  ${LIBS})

add_dependencies(05_StackLinearList
  ${LIBS})