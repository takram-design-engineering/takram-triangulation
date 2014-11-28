//
//  takram/triangulation/triangulation.h
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

#pragma once
#ifndef TAKRAM_TRIANGULATION_TRIANGULATION_H_
#define TAKRAM_TRIANGULATION_TRIANGULATION_H_

#include <algorithm>
#include <cstddef>
#include <vector>

#include "takram/triangulation/point.h"

struct triangulateio;

namespace takram {
namespace triangulation {

class TriangleIterator;

class Triangulation final {
 public:
  enum class Type {
    DELAUNAY,
    CONSTRAINED_DELAUNAY,
    CONFORMING_CONSTRAINED_DELAUNAY,
    VORONOI
  };

  // Constructors
  Triangulation();
  ~Triangulation();

  // Disallow copy and assign
  Triangulation(const Triangulation&) = delete;
  Triangulation& operator=(const Triangulation&) = delete;

  // Performing triangulation
  template <typename Vec2>
  bool operator()(const std::vector<Vec2>& points);
  bool operator()(const std::vector<Point>& points);
  bool operator()(const std::vector<double>& points);

  // Iterators
  TriangleIterator begin() const;
  TriangleIterator end() const;

 private:
  // Clear and deallocate the result
  void clearResult();

  // Data members
  struct triangulateio *result_;
};

#pragma mark - Inline Implementations

inline Triangulation::Triangulation()
    : result_(nullptr) {}

inline Triangulation::~Triangulation() {
  clearResult();
}

#pragma mark Functional operators

template <typename Vec2>
inline bool Triangulation::operator()(const std::vector<Vec2>& points) {
  std::size_t index = 0;
  std::vector<Point> indexed_point(points.size());
  std::transform(
      points.begin(), points.end(), indexed_point.begin(),
      [&index](const Vec2& point) {
        return Point(point.x, point.y, index++);
      });
  return operator()(indexed_point);
}

}  // namespace triangulation
}  // namespace takram

#endif  // TAKRAM_TRIANGULATION_TRIANGULATION_H_
