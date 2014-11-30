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

#include <limits>
#include <vector>

extern "C" {

#define VOID void
#include "triangle/triangle.h"
#undef VOID

}  // extern "C"

#include "glog/logging.h"

#include "takram/triangulation/line_iterator.h"

namespace takram {
namespace triangulation {

#pragma mark Performing triangulation

bool VoronoiTriangulator::operator()(const std::vector<double>& points) {
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
  std::unique_ptr<struct triangulateio> out(new struct triangulateio);
  std::memset(in.get(), 0, sizeof(*in));
  std::memset(out.get(), 0, sizeof(*out));
  in->pointlist = const_cast<double *>(points.data());
  in->numberofpoints = static_cast<Size>(point_size / 2);

  // Perform triangulation
  triangulate(const_cast<char *>("vzQ"), in.get(), out.get(), out_->get());
  return true;
}

#pragma mark Iterators

LineIterator VoronoiTriangulator::begin() const {
  if (out_) {
    return LineIterator(out_->ptr->edgelist,
                        out_->ptr->pointlist,
                        out_->ptr->normlist);
  }
  return LineIterator();
}

LineIterator VoronoiTriangulator::end() const {
  if (out_) {
    return LineIterator(
        out_->ptr->edgelist + out_->ptr->numberofedges * 2,
        out_->ptr->pointlist,
        out_->ptr->normlist);
  }
  return LineIterator();
}

}  // namespace triangulation
}  // namespace takram
