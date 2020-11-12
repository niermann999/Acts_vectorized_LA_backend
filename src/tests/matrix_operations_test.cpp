/**
 * Vectorization Callenge, part of the ACTS project (GSoC 2022)
 *
 * (c) 2022 CERN for the benefit of the ACTS project
 *
 * Mozilla Public License Version 2.0
 */

#include "data/fixtures.hpp"
#include "matrix_operations.hpp"

#include <gtest/gtest.h>

using namespace vec_challenge;

// Sets up test data
using DefaultSetup_Eigen = data::MatrixTest<eigen_vec4_t, eigen_mat4x4_t>;
using DefaultSetup_Vc = data::MatrixTest<vc_vec4_t, vc_mat4x4_t>;

// Data vor vectorized solution (same as default)
using YourSetup = DefaultSetup_Vc;
// Custom setup instead (optional, but make sure it is equivalent for testing!)
// using YourSetup  = data::YourTest;

//----------------------------------------------------Define Tests

//
// Consistency of unittests
//
TEST_F(DefaultSetup_Eigen, TestData_EigenAdd) {
  // Test consistency of test data (do this only once)
  for (std::size_t i = 0; i < m_matrices_a.size(); i++) {
    ASSERT_TRUE(m_matrices_a[i] + m_matrices_b[i] == m_result_add[i]);
  }
}

TEST_F(DefaultSetup_Eigen, TestData_EigenMul) {
  // Test consistency of test data (do this only once)
  for (std::size_t i = 0; i < m_matrices_a.size(); i++) {
    ASSERT_TRUE(m_matrices_a[i] * m_matrices_b[i] == m_result_mul[i]);
  }
}

//
// Test the implementation
//

/// Eigen matrix addition
TEST_F(DefaultSetup_Eigen, EigenTestAdd) {
  // Prepare output
  std::vector<eigen_mat4x4_t> results;
  results.reserve(m_matrices_a.size());

  // Test Eigen implementation
  addition::eigen(m_matrices_a, m_matrices_b, results);

  ASSERT_TRUE(results.size() == m_result_add.size());
  for (std::size_t i = 0; i < m_matrices_a.size(); i++) {
    // Only really works for the controlled integer unittest data!
    ASSERT_EQ(results.at(i), m_result_add.at(i));
  }
}

/// Eigen matrix multiplication
TEST_F(DefaultSetup_Eigen, EigenTestMul) {
  // Prepare output
  std::vector<eigen_mat4x4_t> results;
  results.reserve(m_matrices_a.size());

  // Test Eigen implementation
  multiplication::eigen(m_matrices_a, m_matrices_b, results);

  //ASSERT_TRUE(m_result.size() == m_result_mul.size());
  for (std::size_t i = 0; i < m_matrices_a.size(); i++) {
    ASSERT_EQ(results.at(i), m_result_mul.at(i));
  }
}

/// Vc matrix addition (example implementation)
TEST_F(DefaultSetup_Vc, SolutionTestAdd) {
  // Prepare output
  std::vector<vc_mat4x4_t> results;
  results.reserve(m_matrices_a.size());

  // Test Vc implementation
  addition::vectorized(m_matrices_a, m_matrices_b, results);

  ASSERT_TRUE(results.size() == m_result_add.size());
  for (std::size_t i = 0; i < m_matrices_a.size(); i++) {
    EXPECT_EQ(results.at(i), m_result_add.at(i));
  }
}

/// Vc matrix addition (example implementation)
TEST_F(DefaultSetup_Vc, SolutionTestMul) {
  // Prepare output
  std::vector<vc_mat4x4_t> results;
  results.reserve(m_matrices_a.size());

  // Test Vc implementation
  multiplication::vectorized(m_matrices_a, m_matrices_b, results);

  ASSERT_TRUE(results.size() == m_result_mul.size());
  for (std::size_t i = 0; i < m_matrices_a.size(); i++) {
    EXPECT_EQ(results.at(i), m_result_mul.at(i));
  }
}

//----------------------------------------------------Run Tests

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}