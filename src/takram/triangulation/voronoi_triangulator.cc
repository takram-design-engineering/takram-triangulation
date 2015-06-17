//
//  takram/triangulation/voronoi_triangulator.cc
//
//  MIT License
//
//  Copyright (C) 2014-2015 Shota Matsuda
//
//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.
//

#include "takram/triangulation/voronoi_triangulator.h"

#include <cassert>
#include <cstddef>
#include <cstring>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "takram/triangulation/edge_iterator.h"
#include "takram/triangulation/library.h"
#include "takram/triangulation/types.h"

namespace takram {
namespace triangulation {

#pragma mark Triangulation

bool VoronoiTriangulator::operator()(const std::vector<Real>& points) {
  const auto size = points.size();
  using Size = decltype(triangulateio::numberofpoints);
  if (size > std::numeric_limits<Size>::max()) {
    // The number of points exceeds the limit of the triangle library.
    return false;
  } else if (size < 3) {
    // The provided parameter must have at least 3 points.
    return false;
  }
  // Prepare data
  result_ = std::make_shared<Result>();
  Result out;
  struct triangulateio in;
  std::memset(&in, 0, sizeof(in));
  std::vector<Real> mutable_points(points);
  in.pointlist = mutable_points.data();
  in.numberofpoints = size / 2;

  // Triangulation
  return Triangulator::operator()("vzQ", &in, &*out, &**result_);
}

#pragma mark Attributes

std::size_t VoronoiTriangulator::size() const {
  assert(result_);
  return (*result_)->numberofedges;
}

#pragma mark Iterators

EdgeIterator VoronoiTriangulator::begin() const {
  assert(result_);
  return EdgeIterator(result_);
}

EdgeIterator VoronoiTriangulator::end() const {
  assert(result_);
  const auto end = (*result_)->edgelist + (*result_)->numberofedges;
  return EdgeIterator(result_, end);
}

}  // namespace triangulation
}  // namespace takram
