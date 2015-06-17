//
//  takram/triangulation/triangulator.h
//
//  MIT License
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

#pragma once
#ifndef TAKRAM_TRIANGULATION_TRIANGULATOR_H_
#define TAKRAM_TRIANGULATION_TRIANGULATOR_H_

#include <algorithm>
#include <cstddef>
#include <limits>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "takram/triangulation/point.h"
#include "takram/triangulation/result.h"
#include "takram/triangulation/types.h"

struct triangulateio;

namespace takram {
namespace triangulation {

class Triangulator {
 public:
  Triangulator();
  virtual ~Triangulator() = 0;

  // Copy semantics
  Triangulator(const Triangulator& other) = default;
  Triangulator& operator=(const Triangulator& other) = default;

  // Triangulation
  template <class Container>
  bool operator()(const Container& container);
  bool operator()(std::vector<Point>&& points);
  bool operator()(const std::vector<Point>& points);
  virtual bool operator()(const std::vector<Real>& coordinates) = 0;
  void clear();

  // Parameters
  Real min_angle() const;
  void set_min_angle(double value);
  Real max_area() const;
  void set_max_area(double value);
  int max_steiner_points() const;
  void set_max_steiner_points(int value);

  // Attributes
  bool empty() const { return !result_; }
  virtual std::size_t size() const = 0;

 protected:
  // Triangulation
  bool operator()(const std::string& options,
                  struct triangulateio *in,
                  struct triangulateio *out,
                  struct triangulateio *voronoi);

 protected:
  std::shared_ptr<Result> result_;

 private:
  Real min_angle_;
  Real max_area_;
  int max_steiner_points_;
};

#pragma mark -

inline Triangulator::Triangulator()
    : min_angle_(std::numeric_limits<double>::quiet_NaN()),
      max_area_(std::numeric_limits<double>::quiet_NaN()),
      max_steiner_points_(-1) {}

inline Triangulator::~Triangulator() {}

#pragma mark Triangulation

template <class Container>
inline bool Triangulator::operator()(const Container& container) {
  std::vector<Point> points(container.size());
  std::copy(container.begin(), container.end(), points.begin());
  return operator()(std::move(points));
}

inline bool Triangulator::operator()(std::vector<Point>&& points) {
  std::size_t index{};
  for (auto& point : points) {
    point.index = index++;
  }
  return operator()(points);
}

inline void Triangulator::clear() {
  result_.reset<Result>(nullptr);
}

#pragma mark Parameters

inline Real Triangulator::min_angle() const {
  return min_angle_;
}

inline void Triangulator::set_min_angle(Real value) {
  min_angle_ = value;
}

inline Real Triangulator::max_area() const {
  return max_area_;
}

inline void Triangulator::set_max_area(Real value) {
  max_area_ = value;
}

inline int Triangulator::max_steiner_points() const {
  return max_steiner_points_;
}

inline void Triangulator::set_max_steiner_points(int value) {
  max_steiner_points_ = value;
}

}  // namespace triangulation

using triangulation::Triangulator;

}  // namespace takram

#endif  // TAKRAM_TRIANGULATION_TRIANGULATOR_H_
