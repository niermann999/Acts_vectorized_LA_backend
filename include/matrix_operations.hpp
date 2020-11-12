/**
 * Vectorization Callenge, part of the ACTS project (GSoC 2022)
 *
 * (c) 2022 CERN for the benefit of the ACTS project
 *
 * Mozilla Public License Version 2.0
 */

#include "definitions/types.hpp"

#pragma once

namespace vec_challenge {

template<template<typename> class allocator_t>
using eigen_matrix_collection = 
                    std::vector<eigen_mat4x4_t, allocator_t<eigen_mat4x4_t>>;
template<template<typename> class allocator_t>
using vc_matrix_collection = 
                    std::vector<vc_mat4x4_t, allocator_t<vc_mat4x4_t>>;
//
// Addition
//
namespace addition {

template<template<typename> class allocator_t = std::allocator>
void eigen(eigen_matrix_collection<allocator_t>& matrices_a, 
           eigen_matrix_collection<allocator_t>& matrices_b, eigen_matrix_collection<allocator_t>& results) {
    // Loop over data
    for (std::size_t i = 0; i < matrices_a.size(); ++i) {
        results.emplace_back(matrices_a[i] + matrices_b[i]);
    }
}

template<template<typename> class allocator_t = std::allocator>
void vectorized(vc_matrix_collection<allocator_t>& matrices_a, 
                vc_matrix_collection<allocator_t>& matrices_b, vc_matrix_collection<allocator_t>& results) {
    // Loop over data
    for (std::size_t i = 0; i < matrices_a.size(); ++i) {
        // Advance the memory mapping
        results.emplace_back(matrices_a[i].v0 + matrices_b[i].v0, 
                             matrices_a[i].v1 + matrices_b[i].v1, 
                             matrices_a[i].v2 + matrices_b[i].v2, 
                             matrices_a[i].v3 + matrices_b[i].v3);
    }
}

} // namespace addition

//
// Multiplication
//

namespace multiplication {

template<template<typename> class allocator_t = std::allocator>
void eigen(eigen_matrix_collection<allocator_t>& matrices_a, 
           eigen_matrix_collection<allocator_t>& matrices_b, eigen_matrix_collection<allocator_t>& results) {
    // Loop over data
    for (std::size_t i = 0; i < matrices_a.size(); ++i) {
        results.emplace_back(matrices_a[i] * matrices_b[i]);
    }
}

template<template<typename> class allocator_t = std::allocator>
void vectorized(vc_matrix_collection<allocator_t>& /*matrices_a*/, 
                vc_matrix_collection<allocator_t>& /*matrices_b*/, vc_matrix_collection<allocator_t>& /*results*/) {
    // ?
}

} // namespace multiplication

} // namespace vec_challenge