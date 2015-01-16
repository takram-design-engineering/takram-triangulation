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
#include <ostream>

namespace takram {
namespace triangulation {

class Point final {
 public:
  // Constructors
  Point();
  explicit Point(const double *xy);
  Point(double x, double y);
  Point(double x, double y, std::size_t index);
  Point(const Point& other) = default;

  // Assignment
  Point& operator=(const Point& other) = default;
  void set(const double *xy);
  void set(double x, double y);
  void set(double x, double y, std::size_t index);

  // Comparison
  bool operator==(const Point& other) const;
  bool operator!=(const Point& other) const { return !operator==(other); }
  bool operator<(const Point& other) const;
  bool operator>(const Point& other) const;
  bool operator<=(const Point& other) const;
  bool operator>=(const Point& other) const;

  // Index comparator
  static bool CompareIndex(const Point& a, const Point& b);

  // Stream
  friend std::ostream& operator<<(std::ostream& os, const Point& value);

  // Properties
  double x;
  double y;
  std::size_t index;
};

#pragma mark - Inline Implementations

inline Point::Point()
    : x(),
      y(),
      index() {}

inline Point::Point(const double *xy)
    : x(xy[0]),
      y(xy[1]),
      index() {}

inline Point::Point(double x, double y)
    : x(x),
      y(y),
      index() {}

inline Point::Point(double x, double y, std::size_t index)
    : x(x),
      y(y),
      index(index) {}

#pragma mark Assignment

inline void Point::set(const double *xy) {
  this->x = xy[0];
  this->y = xy[1];
}

inline void Point::set(double x, double y) {
  this->x = x;
  this->y = y;
}

inline void Point::set(double x, double y, std::size_t index) {
  this->x = x;
  this->y = y;
  this->index = index;
}

#pragma mark Comparison

inline bool Point::operator==(const Point &other) const {
  return x == other.x && y == other.y;
}

inline bool Point::operator<(const Point& other) const {
  return x < other.x || (x == other.x && y < other.y);
}

inline bool Point::operator>(const Point& other) const {
  return x > other.x || (x == other.x && y > other.y);
}

inline bool Point::operator<=(const Point& other) const {
  return operator<(other) || operator==(other);
}

inline bool Point::operator>=(const Point& other) const {
  return operator>(other) || operator==(other);
}

#pragma mark Index comparator

inline bool Point::CompareIndex(const Point& a, const Point& b) {
  return a.index < b.index;
}

#pragma mark Stream

inline std::ostream& operator<<(std::ostream& os, const Point& value) {
  os << "( " << value.x << ", " << value.y << " )";
  return os;
}

}  // namespace triangulation
}  // namespace takram

#endif  // TAKRAM_TRIANGULATION_POINT_H_
