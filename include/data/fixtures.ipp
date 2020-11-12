/**
 * Vectorization Callenge, part of the ACTS project (GSoC 2022)
 *
 * (c) 2022 CERN for the benefit of the ACTS project
 *
 * Mozilla Public License Version 2.0
 */

#include <algorithm>
#include <cstdlib>
#include <ctime>

namespace vec_challenge {

namespace data {

/// For linear algebra types that can be initialized by a static member "Random"
/// Both Eigen and Vc define this for their types.
template<typename alg_object_t, template<typename> class allocator_t>
void fill_random(std::vector<alg_object_t, allocator_t<alg_object_t>>& collection) {
   // Generate a vector of the right type with random values
   auto rand_obj = [&](){ return alg_object_t::Random(); };

   std::generate(collection.begin(), collection.end(), rand_obj);
}

//----------------------------------------------------Fill Data Types

/// Default setup of matrix data
template<typename vector_t, typename matrix_t, 
         template<typename> class allocator_t>
void MatrixBenchmark<vector_t, matrix_t, allocator_t>::SetUp(const ::benchmark::State& state) {
   // Only the first thread sets the test env up
   if (state.thread_index() != 0) return;

   // state.range(0) number of vectors/matrices to build in a specific benchmark
   m_vectors = std::vector<vector_t, allocator_t<vector_t>>(state.range(0));
   m_matrices_a = std::vector<matrix_t, allocator_t<matrix_t>>(state.range(0));
   m_matrices_b = std::vector<matrix_t, allocator_t<matrix_t>>(state.range(0));

   fill_random(m_vectors);
   fill_random(m_matrices_a);
   fill_random(m_matrices_b);
}

template<typename vector_t, typename matrix_t, 
            template<typename> class allocator_t>
void MatrixBenchmark<vector_t, matrix_t, allocator_t>::TearDown(const ::benchmark::State& state) {
   // Only one thread frees recources
   if (state.thread_index() != 0) return;

   m_vectors.clear();
   m_matrices_a.clear();
   m_matrices_b.clear();
}

/// Setup for testing data
template<typename vector_t, typename matrix_t>
void MatrixTest<vector_t, matrix_t>::SetUp() {

   // Vector data
   m_vectors = {vector_t{1, 0, 0, 0},
                vector_t{0, 1, 0, 0},
                vector_t{0, 1, 2, 0},
                vector_t{1, 1, 0, 0}};

   // Matrix data
   m_matrices_a = {
         // First matrix
         matrix_t{{0, 1, 0, 0},
         {1, 2, 3, 4},
         {18, 2, 0, 5},
         {90, 22, 1, 67}},
         // Second Matrix
         matrix_t{{0, 0, 4, 0},
         {1, 10, 3, 4},
         {20, 2, 5, 7},
         {3, 7, 13, 5}},
         // Third Matrix
         matrix_t{{3, 25, 9, 0},
         {100, 10, 7, 5},
         {3, 6, 6, 70},
         {56, 1, 3, 0}},
         // Fourth matrix
         matrix_t{{0, 0, 4, 0},
         {1, 10, 3, 4},
         {6, 6, 6, 0},
         {32, 0, 4, 8}}};

   m_matrices_b = {
         // First matrix
         matrix_t{{5, 8, 9, 23},
         {18, 3, 98, 0},
         {55, 1, 1, 8},
         {4, 1, 78, 0}},
         // Second Matrix
         matrix_t{{1, 2, 3, 4}, 
         {5, 6, 7, 8},
         {9, 10, 11, 12},
         {0, 4, 9, 1}},
         // Third matrix
         matrix_t{{34, 7, 0, 3},
         {5, 14, 9, 0}, 
         {9, 9, 2, 31},
         {1, 2, 16, 3}},
         // Fourth matrix
         matrix_t{{1, 1, 1, 1},
         {2, 2, 2, 3},
         {3, 4, 4, 4},
         {5, 2, 44, 1}}};

   m_result_add = {
         // First matrix
         matrix_t{{5, 9, 9, 23},
         {19, 5, 101, 4},
         {73, 3, 1, 13},
         {94, 23, 79, 67}},
         // Second Matrix
         matrix_t{{1, 2, 7, 4},
         {6, 16, 10, 12},
         {29, 12, 16, 19},
         {3, 11, 22, 6}},
         // Third Matrix
         matrix_t{{37, 32, 9, 3},
         {105, 24, 16, 5},
         {12, 15, 8, 101},
         {57, 3, 19, 3}},
         // Fourth matrix
         matrix_t{{1, 1, 5, 1},
         {3, 12, 5, 7},
         {9, 10, 10, 4},
         {37, 2, 48, 9}}};

   m_result_mul = {
         // First matrix
         matrix_t{{18, 3, 98, 0},
         {222, 21, 520, 47},
         {146, 155, 748, 414},
         {1169, 854, 8193, 2078}},
         // Second Matrix
         matrix_t{{36, 40, 44, 48},
         {78, 108, 142, 124},
         {75, 130, 192, 163},
         {155, 198, 246, 229}},
         // Third Matrix
         matrix_t{{308, 452, 243, 288},
         {3518, 913, 184, 532},
         {256, 299, 1186, 405},
         {1936, 433, 15, 261}},
         // Fourth matrix
         matrix_t{{12, 16, 16, 16},
         {50, 41, 209, 47},
         {36, 42, 42, 48},
         {84, 64, 400, 56}}};
}

/// Tear down for unittest data
template<typename vector_t, typename matrix_t>
void MatrixTest<vector_t, matrix_t>::TearDown() {
   m_vectors.clear();
   m_matrices_a.clear();
   m_matrices_b.clear();
   m_result_add.clear();
   m_result_mul.clear();
}

//
// Custom setup of matrix data
//

/// Custom setup for benchmark data
void YourBenchmark::SetUp(const ::benchmark::State& /*state*/) {}
void YourBenchmark::TearDown(const ::benchmark::State& /*state*/) {}

/// Custom setup for unittest data
void YourTest::SetUp() {}
void YourTest::TearDown() {}

} // namespace data

} //namespace vec_challenge