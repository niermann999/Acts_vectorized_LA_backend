# Vectorization Callenge, part of the ACTS project (GSoC 2022)
#
# (c) 2022 CERN for the benefit of the ACTS project
#
# Mozilla Public License Version 2.0

macro(add_unittest _name)

  # automatically prefix the target name
  set(_target "Test${_name}")
  add_executable(${_target} ${ARGN})

  target_include_directories(
    ${_target}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
  )

  target_link_libraries(
    ${_target}
    PRIVATE
    Core
    benchmark::benchmark
    benchmark::benchmark_main
    GTest::gtest
    GTest::gtest_main
    Eigen3::Eigen
    Vc::Vc
  )

  # register as unittest executable
  add_test(NAME ${_name} COMMAND ${_target})

  # install test
  install( TARGETS ${_target} RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}" )
  
endmacro()

add_unittest(_Matrix_Operations matrix_operations_test.cpp)