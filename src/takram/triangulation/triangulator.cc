//
//  takram/triangulation/triangulator.cc
//
//  The MIT License
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

#include "takram/triangulation/triangulator.h"

#include <algorithm>
#include <cmath>
#include <functional>
#include <string>
#include <vector>

#include "takram/triangulation/library.h"
#include "takram/triangulation/types.h"

namespace takram {
namespace triangulation {

namespace {

using PointRef = std::reference_wrapper<const Point>;

inline bool Identify(const PointRef& a, const PointRef& b) {
  return a.get().vector == b.get().vector;
}

inline bool Compare(const PointRef& a, const PointRef& b) {
  return a.get().vector < b.get().vector;
}

inline bool CompareIndex(const PointRef& a, const PointRef& b) {
  return a.get().index < b.get().index;
}

}  // namespace

#pragma mark Triangulation

bool Triangulator::operator()(const std::vector<Point>& points) {
  // Sort and unique will remove lots of points we don't need
  std::vector<PointRef> refs(points.begin(), points.end());
  std::sort(refs.begin(), refs.end(), Compare);
  refs.erase(std::unique(refs.begin(), refs.end(), Identify), refs.end());

  // Sort again, now on their indexes
  std::sort(refs.begin(), refs.end(), CompareIndex);
  std::vector<Real> coordinates;
  for (const auto& ref : refs) {
    coordinates.emplace_back(ref.get().x);
    coordinates.emplace_back(ref.get().y);
  }
  return operator()(coordinates);
}

bool Triangulator::operator()(const std::string& options,
                              struct triangulateio *in,
                              struct triangulateio *out,
                              struct triangulateio *voronoi) {
  std::string parameters;
  if (!std::isnan(min_angle_)) {
    parameters += "q" + std::to_string(min_angle_);
  }
  if (!std::isnan(max_area_)) {
    parameters += "a" + std::to_string(max_area_);
  }
  if (max_steiner_points_ >= 0) {
    parameters += "S" + std::to_string(max_steiner_points_);
  }
  std::vector<char> switches(options.begin(), options.end());
  switches.insert(switches.end(), parameters.begin(), parameters.end());
  switches.emplace_back('\0');
  ::triangulate(switches.data(), in, out, voronoi);
  return true;
}

}  // namespace triangulation
}  // namespace takram
