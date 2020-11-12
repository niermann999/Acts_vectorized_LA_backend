# Vectorization Callenge, part of the ACTS project (GSoC 2022)
#
# (c) 2022 CERN for the benefit of the ACTS project
#
# Mozilla Public License Version 2.0

# CMake include(s).
cmake_minimum_required( VERSION 3.11 )
include( FetchContent )

# Tell the user what's happening.
message( STATUS "Building Google Benchmark" )

# Declare where to get Google Benchmark from.
set( BENCHMARK_SOURCE
   "URL;https://github.com/google/benchmark/archive/refs/tags/v1.6.0.tar.gz;URL_MD5;a7cb118b00430e22cb16774a28fce7ec"
   CACHE STRING "Source for Google Benchmark, when built as part of this project" )
mark_as_advanced( BENCHMARK_SOURCE )
FetchContent_Declare( Benchmark ${BENCHMARK_SOURCE} )

# Options used in the build of Google Benchmark.
set( BENCHMARK_ENABLE_TESTING OFF CACHE BOOL
   "Turn off the tests in Google Benchmark" )

# Get it into the current directory.
FetchContent_Populate( Benchmark )
add_subdirectory( "${benchmark_SOURCE_DIR}" "${benchmark_BINARY_DIR}"
   EXCLUDE_FROM_ALL )
