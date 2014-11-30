//
//  takram/triangulation/triangulator_base.h
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
#ifndef TAKRAM_TRIANGULATION_TRIANGULATOR_BASE_H_
#define TAKRAM_TRIANGULATION_TRIANGULATOR_BASE_H_

#include <algorithm>
#include <cstddef>
#include <memory>
#include <vector>

#include "takram/triangulation/point.h"

struct triangulateio;

namespace takram {
namespace triangulation {

class TriangulatorBase {
 public:
  // Constructors
  TriangulatorBase() {}
  TriangulatorBase(const TriangulatorBase& other);
  virtual ~TriangulatorBase() = 0;

  // Assignment
  TriangulatorBase& operator=(const TriangulatorBase& other);

  // Performing triangulation
  template <typename Vec2>
  bool operator()(const std::vector<Vec2>& points);
  virtual bool operator()(const std::vector<Point>& points);
  virtual bool operator()(const std::vector<double>& points) = 0;

 protected:
  struct Out final {
    Out();
    ~Out();
    struct triangulateio * get() { return ptr.get(); }
    std::unique_ptr<struct triangulateio> ptr;
  };

  // Data members
  std::shared_ptr<Out> out_;
};

#pragma mark - Inline Implementations

inline TriangulatorBase::TriangulatorBase(const TriangulatorBase& other)
    : out_(other.out_) {}

inline TriangulatorBase::~TriangulatorBase() {}

#pragma mark Assignment

inline TriangulatorBase& TriangulatorBase::operator=(
    const TriangulatorBase& other) {
  TriangulatorBase::operator=(other);
  if (&other != this) {
    out_ = other.out_;
  }
  return *this;
}

#pragma mark Functional operators

template <typename Vec2>
inline bool TriangulatorBase::operator()(const std::vector<Vec2>& points) {
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

#endif  // TAKRAM_TRIANGULATION_TRIANGULATOR_BASE_H_
