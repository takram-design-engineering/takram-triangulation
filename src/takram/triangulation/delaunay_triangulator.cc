//
//  takram/triangulation/delaunay_triangulator.cc
//
//  MIT License
//
//  Copyright (C) 2014 Shota Matsuda
//  Copyright (C) 2014 takram design engineering
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

#include "takram/triangulation/delaunay_triangulator.h"

#include <cassert>
#include <cstdlib>
#include <limits>
#include <memory>
#include <string>
#include <vector>

extern "C" {

#define VOID void
#include "triangle/triangle.h"
#undef VOID

}  // extern "C"

#include "glog/logging.h"

#include "takram/triangulation/triangle.h"
#include "takram/triangulation/triangle_iterator.h"

namespace takram {
namespace triangulation {

#pragma mark Performing triangulation

bool DelaunayTriangulator::operator()(const std::vector<double>& points) {
  const auto size = points.size();
  using Size = decltype(triangulateio::numberofpoints);
  if (size > std::numeric_limits<Size>::max()) {
    LOG(ERROR) << "The number of points " << size <<
        " exceeds the limit " << std::numeric_limits<Size>::max() << "." <<
        " This is a limitation of the triangle library.";
    return false;
  } else if (size < 6) {
    LOG(ERROR) << "The provided parameter must have at least 3 points.";
    return false;
  }
  // Prepare data
  result_ = std::make_shared<TriangulatorBase::Result>();
  struct triangulateio in;
  std::memset(&in, 0, sizeof(in));
  std::vector<double> mutable_points(points);
  in.pointlist = mutable_points.data();
  in.numberofpoints = size / 2;

  // Perform triangulation
  std::string options;
  std::vector<Size> segments;
  switch (type_) {
    case Type::DEFAULT:
      options = "zQ";
      break;
    case Type::CONSTRAINED:
      options = "pzQ";
      // Build edges including the one between front and back
      for (Size i = 0; i < size - 1; ++i) {
        segments.emplace_back(i);
        segments.emplace_back(i + 1);
      }
      segments.emplace_back(segments.back());
      segments.emplace_back(segments.front());
      in.segmentlist = segments.data();
      in.numberofsegments = size / 2;
      break;
    case Type::CONFORMING:
      options = "zDQ";
      break;
    case Type::CONSTRAINED_CONFORMING:
      options = "pzDQ";
      // Build edges including the one between front and back
      for (Size i = 0; i < size - 1; ++i) {
        segments.emplace_back(i);
        segments.emplace_back(i + 1);
      }
      segments.emplace_back(segments.back());
      segments.emplace_back(segments.front());
      in.segmentlist = segments.data();
      in.numberofsegments = size / 2;
      break;
    default:
      assert(false);
      break;
  }
  return TriangulatorBase::operator()(options, &in, &**result_, nullptr);
}

#pragma mark Properties

std::size_t DelaunayTriangulator::size() const {
  if (!result_) {
    return 0;
  }
  return (*result_)->numberoftriangles / 3;
}

#pragma mark Iterators

TriangleIterator DelaunayTriangulator::begin() const {
  if (result_) {
    return TriangleIterator((*result_)->trianglelist, (*result_)->pointlist);
  }
  return TriangleIterator();
}

TriangleIterator DelaunayTriangulator::end() const {
  if (result_) {
    return TriangleIterator(
        (*result_)->trianglelist + (*result_)->numberoftriangles * 3,
        (*result_)->pointlist);
  }
  return TriangleIterator();
}

}  // namespace triangulation
}  // namespace takram
