//
//  takram/triangulation/voronoi_triangulator.cc
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

#include "takram/triangulation/voronoi_triangulator.h"

#include <cstddef>
#include <cstring>
#include <limits>
#include <memory>
#include <string>
#include <vector>

extern "C" {

#define VOID void
#include "triangle.h"
#undef VOID

}  // extern "C"

#include "glog/logging.h"

#include "takram/triangulation/line_iterator.h"

namespace takram {
namespace triangulation {

#pragma mark Performing triangulation

bool VoronoiTriangulator::operator()(const std::vector<double>& points) {
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
  TriangulatorBase::Result out;
  struct triangulateio in;
  std::memset(&in, 0, sizeof(in));
  std::vector<double> mutable_points(points);
  in.pointlist = mutable_points.data();
  in.numberofpoints = size / 2;

  // Perform triangulation
  return TriangulatorBase::operator()("vzQ", &in, &*out, &**result_);
}

#pragma mark Properties

std::size_t VoronoiTriangulator::size() const {
  if (!result_) {
    return 0;
  }
  return (*result_)->numberofedges / 2;
}

#pragma mark Iterators

LineIterator VoronoiTriangulator::begin() const {
  if (result_) {
    return LineIterator((*result_)->edgelist,
                        (*result_)->pointlist,
                        (*result_)->normlist);
  }
  return LineIterator();
}

LineIterator VoronoiTriangulator::end() const {
  if (result_) {
    return LineIterator(
        (*result_)->edgelist + (*result_)->numberofedges * 2,
        (*result_)->pointlist,
        (*result_)->normlist);
  }
  return LineIterator();
}

}  // namespace triangulation
}  // namespace takram
