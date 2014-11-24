//
//  takram/triangulation/triangulation.cpp
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

#include "takram/triangulation/triangulation.h"

extern "C" {

#define REAL double
#define VOID void
#define ANSI_DECLARATORS
#include <triangle.h>

}  // extern "C"

#include <glog/logging.h>

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <limits>
#include <vector>

#include "takram/triangulation/triangle.h"
#include "takram/triangulation/triangle_iterator.h"

namespace takram {
namespace triangulation {

#pragma mark Performing triangulation

bool Triangulation::operator()(const std::vector<Point>& points) {
  // Sort and unique will remove lots of points we don't need
  std::vector<Point> unique_points(points.size());
  std::copy(points.begin(), points.end(), unique_points.begin());
  std::sort(unique_points.begin(), unique_points.end());
  unique_points.resize(std::distance(
      unique_points.begin(),
      std::unique(unique_points.begin(), unique_points.end())));

  // Sort again, now on their indexes
  std::sort(unique_points.begin(), unique_points.end(), Point::CompareIndex);
  std::vector<double> coordinates;
  for (const auto& point : unique_points) {
    coordinates.emplace_back(point.x());
    coordinates.emplace_back(point.y());
  }
  return operator()(coordinates);
}

bool Triangulation::operator()(const std::vector<double>& points) {
  const auto point_size = points.size();
  using Size = decltype(::triangulateio::numberofpoints);
  if (point_size <= std::numeric_limits<Size>::max()) {
    LOG(ERROR) << "The number of points " << point_size <<
        " exceeds the limit " << std::numeric_limits<Size>::max() << "." <<
        " This is a limitation of the triangle library.";
    return false;
  } else if (point_size < 6) {
    LOG(ERROR) << "The provided parameter must have at least 3 points.";
    return false;
  }
  // Clear the previous result if any
  ClearResult();

  // Build edges including the one between front and back
  std::vector<Size> edges;
  auto points_itr = points.begin();
  ++points_itr;
  for (; points_itr != points.end(); ++points_itr) {
    edges.emplace_back(*std::prev(points_itr));
    edges.emplace_back(*points_itr);
  }
  edges.emplace_back(edges.back());
  edges.emplace_back(edges.front());

  // Perform constrained delaunay triangulation
  struct ::triangulateio in;
  result_ = new struct ::triangulateio;
  std::memset(&in, 0, sizeof(in));
  std::memset(result_, 0, sizeof(*result_));
  in.pointlist = const_cast<double *>(points.data());
  in.numberofpoints = static_cast<Size>(point_size / 2);
  in.segmentlist = edges.data();
  in.numberofsegments = static_cast<Size>(point_size / 2);
  // p: Triangulates a planar straight line graph
  // z: Numbers all items starting from zero
  // Q: Quiet. No terminal output except errors
  ::triangulate(const_cast<char *>("pzQ"), &in, result_, nullptr);
  return true;
}

#pragma mark Iterators

TriangleIterator Triangulation::begin() const {
  if (result_) {
    return TriangleIterator(result_->trianglelist, result_->pointlist);
  }
  return TriangleIterator();
}

TriangleIterator Triangulation::end() const {
  if (result_) {
    return TriangleIterator(
        result_->trianglelist + result_->numberoftriangles * 3,
        result_->pointlist);
  }
  return TriangleIterator();
}

#pragma mark -

void Triangulation::ClearResult() {
  if (result_) {
    std::free(result_->pointlist);
    std::free(result_->pointmarkerlist);
    std::free(result_->pointattributelist);
    std::free(result_->trianglelist);
    std::free(result_->triangleattributelist);
    std::free(result_->trianglearealist);
    std::free(result_->neighborlist);
    std::free(result_->segmentlist);
    std::free(result_->segmentmarkerlist);
    std::free(result_->holelist);
    std::free(result_->regionlist);
    std::free(result_->edgelist);
    std::free(result_->edgemarkerlist);
    std::free(result_->normlist);
    delete result_;
    result_ = nullptr;
  }
}

}  // namespace triangulation
}  // namespace takram
