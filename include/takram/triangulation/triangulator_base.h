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
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "takram/triangulation/point.h"

struct triangulateio;

namespace takram {
namespace triangulation {

class TriangulatorBase {
 public:
  // Constructors
  TriangulatorBase();
  TriangulatorBase(const TriangulatorBase& other);
  virtual ~TriangulatorBase() = 0;

  // Assignment
  TriangulatorBase& operator=(const TriangulatorBase& other);

  // Performing triangulation
  template <typename Vec2>
  bool operator()(const std::vector<Vec2>& points);
  virtual bool operator()(const std::vector<Point>& points);
  virtual bool operator()(const std::vector<double>& points) = 0;
  void clear() { result_.reset<Result>(nullptr); }

  // Parameters
  double min_angle() const { return min_angle_; }
  void set_min_angle(double value) { min_angle_ = value; }
  double max_area() const { return max_area_; }
  void set_max_area(double value) { max_area_ = value; }
  int max_steiner_points() const { return max_steiner_points_; }
  void set_max_steiner_points(int value) { max_steiner_points_ = value; }

  // Properties
  bool empty() const { return !result_; }
  virtual std::size_t size() const = 0;

 protected:
  class Result;

  // Performing triangulation
  bool operator()(const std::string& options,
                  struct triangulateio *in,
                  struct triangulateio *out,
                  struct triangulateio *voronoi);

  // Data members
  double min_angle_;
  double max_area_;
  int max_steiner_points_;
  std::shared_ptr<Result> result_;
};

class TriangulatorBase::Result final {
 public:
  // Constructors
  Result();
  ~Result();

  // Operators
  struct triangulateio& operator*() { return *get(); }
  struct triangulateio * operator->() { return get(); }
  struct triangulateio * get() { return data_.get(); }

 private:
  // Data members
  std::unique_ptr<struct triangulateio> data_;
};

#pragma mark - Inline Implementations

inline TriangulatorBase::TriangulatorBase()
    : min_angle_(std::numeric_limits<double>::quiet_NaN()),
      max_area_(std::numeric_limits<double>::quiet_NaN()),
      max_steiner_points_(-1) {}

inline TriangulatorBase::TriangulatorBase(const TriangulatorBase& other)
    : min_angle_(other.min_angle_),
      max_area_(other.max_area_),
      max_steiner_points_(other.max_steiner_points_),
      result_(other.result_) {}

inline TriangulatorBase::~TriangulatorBase() {}

#pragma mark Assignment

inline TriangulatorBase& TriangulatorBase::operator=(
    const TriangulatorBase& other) {
  TriangulatorBase::operator=(other);
  if (&other != this) {
    min_angle_ = other.min_angle_;
    max_area_ = other.max_area_;
    max_steiner_points_ = other.max_steiner_points_;
    result_ = other.result_;
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
