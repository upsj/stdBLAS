/*
//@HEADER
// ************************************************************************
//
//                        Kokkos v. 2.0
//              Copyright (2019) Sandia Corporation
//
// Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
// the U.S. Government retains certain rights in this software. //
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact Christian R. Trott (crtrott@sandia.gov)
//
// ************************************************************************
//@HEADER
*/

#ifndef LINALG_INCLUDE_EXPERIMENTAL___P1673_BITS_BLAS1_SCALE_HPP_
#define LINALG_INCLUDE_EXPERIMENTAL___P1673_BITS_BLAS1_SCALE_HPP_

namespace std {
namespace experimental {
inline namespace __p1673_version_0 {
namespace linalg {

namespace {

template<class Scalar,
         class inout_vector_t>
void linalg_scale_rank_1(const Scalar alpha,
                         inout_vector_t x)
{
  for (ptrdiff_t i = 0; i < x.extent(0); ++i) {
    x(i) *= alpha;
  }
}

template<class Scalar,
         class inout_matrix_t>
void linalg_scale_rank_2(const Scalar alpha,
                        inout_matrix_t x)
{
  for (ptrdiff_t j = 0; j < x.extent(1); ++j) {
    for (ptrdiff_t i = 0; i < x.extent(0); ++i) {
      x(i,j) *= alpha;
    }
  }
}

// TODO add mdarray specializations; needed so that inout_object_t is
// not passed by value (which would be wrong for a container type like
// mdarray).

}

template<class Scalar,
         class inout_object_t>
void scale(const Scalar alpha,
           inout_object_t x)
{
  if constexpr (x.rank() == 1) {
    linalg_scale_rank_1(alpha, x);
  }
  else if constexpr (x.rank() == 2) {
    linalg_scale_rank_2(alpha, x);
  }
  else {
    static_assert("Not implemented");
  }
}

template<class ExecutionPolicy,
         class Scalar,
         class inout_object_t>
void scale(ExecutionPolicy&& /* exec */,
           const Scalar alpha,
           inout_object_t obj)
{
  scale(alpha, obj);
}

} // end namespace linalg
} // end inline namespace __p1673_version_0
} // end namespace experimental
} // end namespace std

#endif //LINALG_INCLUDE_EXPERIMENTAL___P1673_BITS_BLAS1_SCALE_HPP_
