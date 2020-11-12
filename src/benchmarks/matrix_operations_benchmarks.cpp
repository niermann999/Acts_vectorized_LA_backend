/**
 * Vectorization Callenge, part of the ACTS project (GSoC 2022)
 *
 * (c) 2022 CERN for the benefit of the ACTS project
 *
 * Mozilla Public License Version 2.0
 */
 
#include "data/fixtures.hpp"
#include "matrix_operations.hpp"

#include <benchmark/benchmark.h>

using namespace vec_challenge;

// Sets up test data
template<typename vector_t, typename matrix_t, 
         template<typename> class allocator_t = std::allocator>
using DefaultSetup = data::MatrixBenchmark<vector_t, matrix_t, allocator_t>;
// Data for vectorized solution
using YourSetup = DefaultSetup<vc_vec4_t, vc_mat4x4_t, Vc::Allocator>;
// Custom setup instead (optional)
// using YourSetup = data::YourBenchmark;

// Number of matrices to be used in benchmark
constexpr std::size_t n_matrices = 1000;
// Number of repetitions of function in benchmark
constexpr std::size_t repetitions = 100;

//----------------------------------------------------Define Benchmark

/// Benchmark the solution (addition)
BENCHMARK_DEFINE_F(YourSetup, SolutionBenchmarkAdd)(benchmark::State& state) {
  // Prepare output
  aligned::vc::vector<vc_mat4x4_t> results;
  results.reserve(n_matrices);

  for (auto _ : state) {
    // Prevent the compiler to optimize the benchmark loop away
    benchmark::DoNotOptimize(results);
    // Call the function
    addition::vectorized(m_matrices_a, m_matrices_b, results);
  }
}

/// Benchmark the solution (muliplication)
BENCHMARK_DEFINE_F(YourSetup, SolutionBenchmarkMul)(benchmark::State& state) {
  // Prepare output
  aligned::vc::vector<vc_mat4x4_t> results;
  results.reserve(n_matrices);

  for (auto _ : state) {
    // Prevent the compiler to optimize the benchmark loop away
    benchmark::DoNotOptimize(results);
    // Call the function
    multiplication::vectorized(m_matrices_a, m_matrices_b, results);
  }
}

/// Benchmark the predefined Eigen Implementation (addition)
BENCHMARK_TEMPLATE_DEFINE_F(DefaultSetup, EigenBenchmarkAdd, eigen_vec4_t, eigen_mat4x4_t, Eigen::aligned_allocator)(benchmark::State& state) {
  // Prepare output
  aligned::eigen::vector<eigen_mat4x4_t> results;
  results.reserve(n_matrices);

  for (auto _ : state) {
    // Prevent the compiler to optimize the benchmark loop away
    benchmark::DoNotOptimize(results);
    // Call the function
    addition::eigen(m_matrices_a, m_matrices_b, results);
  }
}
/// Benchmark the predefined Eigen Implementation (muliplication)
BENCHMARK_TEMPLATE_DEFINE_F(DefaultSetup, EigenBenchmarkMul, eigen_vec4_t, eigen_mat4x4_t, Eigen::aligned_allocator)(benchmark::State& state) {
  // Prepare output
  aligned::eigen::vector<eigen_mat4x4_t> results;
  results.reserve(n_matrices);

  for (auto _ : state) {
    // Prevent the compiler to optimize the benchmark loop away
    benchmark::DoNotOptimize(results);
    // Call the function
    multiplication::eigen(m_matrices_a, m_matrices_b, results);
  }
}

//----------------------------------------------------Run Benchmark

BENCHMARK_REGISTER_F(YourSetup, SolutionBenchmarkAdd)
  ->Range(n_matrices, n_matrices)
  ->Name("Solution_Benchmark_Addition")
  ->Repetitions(repetitions)
  ->DisplayAggregatesOnly(true);
  //->ThreadPerCpu();

BENCHMARK_REGISTER_F(DefaultSetup, EigenBenchmarkAdd)
  ->Range(n_matrices, n_matrices)
  ->Name("Eigen_Benchmark_Addition")
  ->Repetitions(repetitions)
  ->DisplayAggregatesOnly(true);
  //->ThreadPerCpu();

BENCHMARK_REGISTER_F(YourSetup, SolutionBenchmarkMul)
  ->Range(n_matrices, n_matrices)
  ->Name("Solution_Benchmark_Multiplication")
  ->Repetitions(repetitions)
  ->DisplayAggregatesOnly(true);
  //->ThreadPerCpu();

BENCHMARK_REGISTER_F(DefaultSetup, EigenBenchmarkMul)
  ->Range(n_matrices, n_matrices)
  ->Name("Eigen_Benchmark_Multiplication")
  ->Repetitions(repetitions)
  ->DisplayAggregatesOnly(true);
  //->ThreadPerCpu();

BENCHMARK_MAIN();