# Vectorization Callenge, part of the ACTS project (GSoC 2022)
#
# (c) 2022 CERN for the benefit of the ACTS project
#
# Mozilla Public License Version 2.0

macro(add_benchmark _name)

  # automatically prefix the target name
  set(_target "Benchmark${_name}")
  add_executable(${_target} ${ARGN})

  target_compile_definitions(
    ${_target}
    PRIVATE "-DBENCHMARK_ENABLE_GTEST_TESTS=OFF"
  )

  add_compile_options(-pthread)

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

  # install benchmark
  install( TARGETS ${_target} RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}" )

endmacro()

add_benchmark(_Matrix_Operations matrix_operations_benchmarks.cpp)