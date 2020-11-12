/**
 * Vectorization Callenge, part of the ACTS project (GSoC 2022)
 *
 * (c) 2022 CERN for the benefit of the ACTS project
 *
 * Mozilla Public License Version 2.0
 */

#include "definitions/types.hpp"

#include <benchmark/benchmark.h>
#include <gtest/gtest.h>

namespace vec_challenge {

namespace data {

//----------------------------------------------------Fill Data Types

/// Default setup of matrix data for benchmark (google benchmark)
template<typename vector_t, typename matrix_t, 
          template<typename> class allocator_t = std::allocator>
class MatrixBenchmark : public benchmark::Fixture {

  public:

  template<typename T>
  using collection_type = std::vector<T, allocator_t<T>>;

  /// Vector data
  std::vector<vector_t, allocator_t<vector_t>> m_vectors;
  /// Matrix data
  std::vector<matrix_t, allocator_t<matrix_t>> m_matrices_a;
  std::vector<matrix_t, allocator_t<matrix_t>> m_matrices_b;

  void SetUp (const ::benchmark::State&);
  void TearDown (const ::benchmark::State&);
};

/// Default setup of matrix data for unittest (google test)
template<typename vector_t, typename matrix_t>
class MatrixTest : public ::testing::Test {

  public:

  /// Vector data
  std::vector<vector_t> m_vectors;
  /// Matric data
  std::vector<matrix_t> m_matrices_a, m_matrices_b;
  std::vector<matrix_t> m_result_add, m_result_mul;

  void SetUp () override;
  void TearDown() override;
};


/// Custom setup of benchmark data
class YourBenchmark : public benchmark::Fixture {
public:
  void SetUp (const ::benchmark::State&);
  void TearDown (const ::benchmark::State&);
};

/// Custom setup of unittest data
class YourTest : public ::testing::Test {
public:
  void SetUp () override;
  void TearDown() override;
};

} // namespace data

} //namespace vec_challenge

#include "data/fixtures.ipp"