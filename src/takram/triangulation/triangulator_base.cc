//
//  takram/triangulation/triangulator_base.cc
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

#include "takram/triangulation/triangulator_base.h"

#include <algorithm>
#include <cstdlib>
#include <vector>

extern "C" {

#define VOID void
#include "triangle/triangle.h"
#undef VOID

}  // extern "C"

namespace takram {
namespace triangulation {

#pragma mark Performing triangulation

bool TriangulatorBase::operator()(const std::vector<Point>& points) {
  // Sort and unique will remove lots of points we don't need
  std::vector<Point> unique_points(points.size());
  std::copy(points.begin(), points.end(), unique_points.begin());
  std::sort(unique_points.begin(), unique_points.end());
  unique_points.resize(std::distance(
      unique_points.begin(),
      std::unique(unique_points.begin(), unique_points.end())));

  // Sort again, now on their indexes
  std::sort(unique_points.begin(), unique_points.end(), Point::compareIndex);
  std::vector<double> coordinates;
  for (const auto& point : unique_points) {
    coordinates.emplace_back(point.x);
    coordinates.emplace_back(point.y);
  }
  return operator()(coordinates);
}

#pragma mark -

TriangulatorBase::Out::Out()
    : ptr(new struct triangulateio) {
  std::memset(ptr.get(), 0, sizeof(*ptr));
}

TriangulatorBase::Out::~Out() {
  std::free(ptr->pointlist);
  std::free(ptr->pointmarkerlist);
  std::free(ptr->pointattributelist);
  std::free(ptr->trianglelist);
  std::free(ptr->triangleattributelist);
  std::free(ptr->trianglearealist);
  std::free(ptr->neighborlist);
  std::free(ptr->segmentlist);
  std::free(ptr->segmentmarkerlist);
  std::free(ptr->holelist);
  std::free(ptr->regionlist);
  std::free(ptr->edgelist);
  std::free(ptr->edgemarkerlist);
  std::free(ptr->normlist);
}

}  // namespace triangulation
}  // namespace takram
