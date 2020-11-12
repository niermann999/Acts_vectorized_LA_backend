/**
 * Vectorization Callenge, part of the ACTS project (GSoC 2022)
 *
 * (c) 2022 CERN for the benefit of the ACTS project
 *
 * Mozilla Public License Version 2.0
 */

#include <array>
#include <initializer_list>
#include <type_traits>
#include <vector>

#include <Eigen/Dense>
#include <Vc/Vc>

#pragma once

namespace vec_challenge {

// Vc
// Raw Vc vector type
#ifdef PRECISION_DOUBLE
using Scalar = double;
using vc_vector_t = Vc::double_v;
#else
using Scalar = float;
using vc_vector_t = Vc::float_v;
#endif

// Vector type for 4D vert. layout: Guaranteed to have 4 entries, for double
// and single precision
#ifdef PRECISION_DOUBLE
using Scalar = double;
using vc_vec4_t = Vc::SimdArray<double, 4>;
#else
using Scalar = float;
using vc_vec4_t = Vc::SimdArray<float, 4>;
// No initializer list available
// using vc_vec4_t = Vc::float_v;
#endif

// Vc matrix type
template<typename vector_t>
struct Matrix4;
using vc_mat4x4_t = Matrix4<vc_vec4_t>;


// Eigen
// Geometric vectors
using eigen_vec4_t = Eigen::Matrix<Scalar, 4, 1>;
using eigen_mat4x4_t = Eigen::Matrix<Scalar, 4, 4>;


// Containers
namespace aligned {

  namespace eigen {

    template <typename T>
    using vector = std::vector<T, Eigen::aligned_allocator<T>>;

  } // namespace eigen

  namespace vc {

    template <typename T>
    using vector = std::vector<T, Vc::Allocator<T>>;

    template<typename T, std::size_t N>
    using array = Vc::array<T, N>;

  } // namespace vc

} // namespace aligned

//
// Geometric helper structs. Generalize the dimension?
//

/// Vc gather scatter type
template<typename scalar_t>
struct Vector4
{
  scalar_t x, y, z, t;
};

/// Matrix type that can be defined by subvectors
template<typename vector_t>
struct Matrix4
{
  using vector_type = vector_t;
  using scalar_type = typename vector_t::value_type;

  /// Default constructor
  Matrix4() = default;

  /// Copy initialization
  Matrix4(vector_t a, vector_t b, vector_t c, vector_t d) :
  v0(a), v1(b), v2(c), v3(d) {}

  /// Initialization from initializer list
  Matrix4(std::initializer_list<std::initializer_list<scalar_type>> &&list_l) :
    v0(list_l.begin()->begin()),
    v1((list_l.begin() + 1)->begin()),
    v2((list_l.begin() + 2)->begin()),
    v3((list_l.begin() + 3)->begin())
  {}

  /// Provide a wrapper implementation for the vector types random init
  template<std::enable_if_t<
           std::is_same_v<vector_t, vc_vec4_t> or 
           std::is_same_v<vector_t, vc_vector_t> or 
           std::is_same_v<vector_t, eigen_vec4_t>, bool> = true>
  static Matrix4<vector_t> Random() {
    return Matrix4<vector_t>(vector_t::Random(), vector_t::Random(), 
                             vector_t::Random(), vector_t::Random());
  }

  /// Equality operator
  inline bool operator==(const Matrix4<vector_t> &other) const {
    bool is_same = true;
    // Vc types need to resolve a boolean mask over the vector
    if constexpr (std::is_same_v<vector_t, vc_vec4_t> or 
                  std::is_same_v<vector_t, vc_vector_t>) {
      is_same &= (v0 == other.v0).isFull();
      is_same &= (v1 == other.v1).isFull();
      is_same &= (v2 == other.v2).isFull();
      is_same &= (v3 == other.v3).isFull();
    }
    else {
      is_same &= (v0 == other.v0);
      is_same &= (v1 == other.v1);
      is_same &= (v2 == other.v2);
      is_same &= (v3 == other.v3);
    }

    return is_same;
  }

  /// Sub vectors of the matrix
  vector_t v0, v1, v2, v3;
};

} //namespace vec_challenge