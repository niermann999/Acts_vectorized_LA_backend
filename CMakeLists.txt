# Vectorization Callenge, part of the ACTS project (GSoC 2022)
#
# (c) 2022 CERN for the benefit of the ACTS project
#
# Mozilla Public License Version 2.0

cmake_minimum_required(VERSION 3.11)
project(Vectorization_Challenge VERSION 0.1 LANGUAGES CXX)

# Make sure we use optimizations
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Set up GoogleTest.
add_subdirectory( externals/googletest )

# Set up Eigen3.
add_subdirectory( externals/eigen3 )

# Set up Google Benchmark.
add_subdirectory( externals/benchmark )

# Set up VC library.
add_subdirectory( externals/vc )

# Define an interface target for the core code
add_library( Core INTERFACE )
target_include_directories( Core INTERFACE ${CMAKE_INSTALL_INCLUDEDIR} ${CMAKE_SOURCE_DIR}/include/ )
target_compile_features( Core INTERFACE cxx_std_17 )

# General compile options
add_compile_options(
       -O3 --std=c++17
       -Wall -Wextra -Wshadow -fstrict-aliasing -Wno-deprecated-declarations -Wno-unused-parameter -Wstrict-aliasing ${Vc_ARCHITECTURE_FLAGS}
)

add_subdirectory(src)