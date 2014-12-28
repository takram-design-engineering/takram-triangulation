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
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

extern "C" {

#define VOID void
#include "triangle.h"
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
  unique_points.erase(std::unique(unique_points.begin(), unique_points.end()),
                      unique_points.end());

  // Sort again, now on their indexes
  std::sort(unique_points.begin(), unique_points.end(), Point::CompareIndex);
  std::vector<double> coordinates;
  for (const auto& point : unique_points) {
    coordinates.emplace_back(point.x);
    coordinates.emplace_back(point.y);
  }
  return operator()(coordinates);
}

bool TriangulatorBase::operator()(const std::string& options,
                                  struct triangulateio *in,
                                  struct triangulateio *out,
                                  struct triangulateio *voronoi) {
  std::string additional_options;
  if (!std::isnan(min_angle_)) {
    additional_options += "q" + std::to_string(min_angle_);
  }
  if (!std::isnan(max_area_)) {
    additional_options += "a" + std::to_string(max_area_);
  }
  if (max_steiner_points_ >= 0) {
    additional_options += "S" + std::to_string(max_steiner_points_);
  }
  std::vector<char> mutable_options(options.begin(), options.end());
  mutable_options.insert(mutable_options.end(),
                         additional_options.begin(),
                         additional_options.end());
  mutable_options.emplace_back('\0');
  triangulate(mutable_options.data(), in, out, voronoi);
  return true;
}

#pragma mark -

TriangulatorBase::Result::Result()
    : data_(std::make_unique<struct triangulateio>()) {
  std::memset(data_.get(), 0, sizeof(*data_));
}

TriangulatorBase::Result::~Result() {
  std::free(data_->pointlist);
  std::free(data_->pointmarkerlist);
  std::free(data_->pointattributelist);
  std::free(data_->trianglelist);
  std::free(data_->triangleattributelist);
  std::free(data_->trianglearealist);
  std::free(data_->neighborlist);
  std::free(data_->segmentlist);
  std::free(data_->segmentmarkerlist);
  std::free(data_->holelist);
  std::free(data_->regionlist);
  std::free(data_->edgelist);
  std::free(data_->edgemarkerlist);
  std::free(data_->normlist);
}

}  // namespace triangulation
}  // namespace takram
