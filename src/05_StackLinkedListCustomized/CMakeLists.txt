cmake_minimum_required(VERSION 3.0.0)

set(SRCS
  05_StackLinkedListCustomized.cpp)

add_executable(05_StackLinkedListCustomized
  ${SRCS})

set(LIBS
  PerformanceStatistics
  Utility)

target_link_libraries(05_StackLinkedListCustomized
  ${LIBS})

add_dependencies(05_StackLinkedListCustomized
  ${LIBS})