# Vectorization Callenge, part of the ACTS project (GSoC 2022)
#
# (c) 2022 CERN for the benefit of the ACTS project
#
# Mozilla Public License Version 2.0

# CMake include(s).
cmake_minimum_required( VERSION 3.11 )
include( FetchContent )

# Tell the user what's happening.
message( STATUS "Building GoogleTest" )

# Declare where to get GoogleTest from.
set( GOOGLETEST_SOURCE
   "URL;https://github.com/google/googletest/archive/release-1.11.0.tar.gz;URL_MD5;e8a8df240b6938bb6384155d4c37d937"
   CACHE STRING "Source for GoogleTest, when built as part of this project" )
mark_as_advanced( GOOGLETEST_SOURCE )
FetchContent_Declare( GoogleTest ${GOOGLETEST_SOURCE} )

# Options used in the build of GoogleTest.
set( BUILD_GMOCK TRUE CACHE BOOL "Turn off the build of GMock" )
set( INSTALL_GTEST FALSE CACHE BOOL "Turn off the installation of GoogleTest" )

# Get it into the current directory.
FetchContent_Populate( GoogleTest )
add_subdirectory( "${googletest_SOURCE_DIR}" "${googletest_BINARY_DIR}"
   EXCLUDE_FROM_ALL )
