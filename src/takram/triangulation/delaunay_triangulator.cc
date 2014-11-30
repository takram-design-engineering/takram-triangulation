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

extern "C" {

#define VOID void
#include "triangle/triangle.h"
#undef VOID

}  // extern "C"

#include <cassert>
#include <cstdlib>
#include <limits>
#include <vector>

#include "glog/logging.h"

#include "takram/triangulation/triangle.h"
#include "takram/triangulation/triangle_iterator.h"

namespace takram {
namespace triangulation {

#pragma mark Performing triangulation

bool DelaunayTriangulator::operator()(const std::vector<double>& points) {
  const auto point_size = points.size();
  using Size = decltype(triangulateio::numberofpoints);
  if (point_size > std::numeric_limits<Size>::max()) {
    LOG(ERROR) << "The number of points " << point_size <<
        " exceeds the limit " << std::numeric_limits<Size>::max() << "." <<
        " This is a limitation of the triangle library.";
    return false;
  } else if (point_size < 6) {
    LOG(ERROR) << "The provided parameter must have at least 3 points.";
    return false;
  }
  // Prepare data
  out_ = std::make_shared<TriangulatorBase::Out>();
  std::unique_ptr<struct triangulateio> in(new struct triangulateio);
  std::memset(in.get(), 0, sizeof(*in));
  in->pointlist = const_cast<double *>(points.data());
  in->numberofpoints = static_cast<Size>(point_size / 2);

  // Perform triangulation
  const char *options;
  switch (type_) {
    case Type::DEFAULT: {
      options = "zQ";
      break;
    }
    case Type::CONSTRAINED: {
      options = "pzQ";
      // Build edges including the one between front and back
      std::vector<Size> segments;
      for (Size i = 0; i < point_size - 1; ++i) {
        segments.emplace_back(i);
        segments.emplace_back(i + 1);
      }
      segments.emplace_back(segments.back());
      segments.emplace_back(segments.front());
      in->segmentlist = segments.data();
      in->numberofsegments = static_cast<Size>(point_size / 2);
      break;
    }
    case Type::CONFORMING_CONSTRAINED: {
      options = "zDQ";
      break;
    }
    default:
      assert(false);
  }
  triangulate(const_cast<char *>(options), in.get(), out_->get(), nullptr);
  return true;
}

#pragma mark Iterators

TriangleIterator DelaunayTriangulator::begin() const {
  if (out_) {
    return TriangleIterator(out_->ptr->trianglelist, out_->ptr->pointlist);
  }
  return TriangleIterator();
}

TriangleIterator DelaunayTriangulator::end() const {
  if (out_) {
    return TriangleIterator(
        out_->ptr->trianglelist + out_->ptr->numberoftriangles * 3,
        out_->ptr->pointlist);
  }
  return TriangleIterator();
}

}  // namespace triangulation
}  // namespace takram
