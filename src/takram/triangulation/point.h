//
//  takram/triangulation/point.h
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
#ifndef TAKRAM_TRIANGULATION_POINT_H_
#define TAKRAM_TRIANGULATION_POINT_H_

#include <cstddef>

namespace takram {
namespace triangulation {

class Point final {
 public:
  // Constructors
  Point();
  explicit Point(const double *xy);
  Point(double x, double y);
  Point(double x, double y, std::size_t index);
  Point(const Point& other);

  // Assignment
  Point& operator=(const Point& other);
  void set(double x, double y);

  // Comparison
  bool operator==(const Point& other) const;
  bool operator!=(const Point& other) const { return !operator==(other); }
  bool operator<(const Point& other) const;
  bool operator>(const Point& other) const;
  bool operator<=(const Point& other) const;
  bool operator>=(const Point& other) const;

  // Index comparator
  static bool CompareIndex(const Point& a, const Point& b);

  // Properties
  double x() const { return x_; }
  void set_x(double value) { x_ = value; }
  double y() const { return y_; }
  void set_y(double value) { y_ = value; }
  std::size_t index() const { return index_; }
  void set_index(std::size_t value) { index_ = value; }

 private:
  // Data members
  double x_;
  double y_;
  std::size_t index_;
};

#pragma mark - Inline Implementations

inline Point::Point()
    : x_(0.0),
      y_(0.0),
      index_(0) {}

inline Point::Point(const double *xy)
    : x_(xy[0]),
      y_(xy[1]),
      index_(0) {}

inline Point::Point(double x, double y)
    : x_(x),
      y_(y),
      index_(0) {}

inline Point::Point(double x, double y, std::size_t index)
    : x_(x),
      y_(y),
      index_(index) {}

inline Point::Point(const Point& other)
    : x_(other.x_),
      y_(other.y_),
      index_(other.index_) {}

#pragma mark Assignment

inline Point& Point::operator=(const Point& other) {
  if (&other != this) {
    x_ = other.x_;
    y_ = other.y_;
    index_ = other.index_;
  }
  return *this;
}

inline void Point::set(double x, double y) {
  x_ = x;
  y_ = y;
}

#pragma mark Comparison

inline bool Point::operator==(const Point &other) const {
  return x_ == other.x_ && y_ == other.y_;
}

inline bool Point::operator<(const Point& other) const {
  return x_ < other.x_ || (x_ == other.x_ && y_ < other.y_);
}

inline bool Point::operator>(const Point& other) const {
  return x_ > other.x_ || (x_ == other.x_ && y_ > other.y_);
}

inline bool Point::operator<=(const Point& other) const {
  return operator<(other) || operator==(other);
}

inline bool Point::operator>=(const Point& other) const {
  return operator>(other) || operator==(other);
}

#pragma mark Index comparator

inline bool Point::CompareIndex(const Point& a, const Point& b) {
  return a.index_ < b.index_;
}

}  // namespace triangulation
}  // namespace takram

#endif  // TAKRAM_TRIANGULATION_POINT_H_
