//
//  takram/triangulation/line.h
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
#ifndef TAKRAM_TRIANGULATION_LINE_H_
#define TAKRAM_TRIANGULATION_LINE_H_

#include "takram/triangulation/point.h"

namespace takram {
namespace triangulation {

class Line final {
 public:
  // Constructors
  Line() {}
  Line(const Point& a, const Point& b, bool finite);
  Line(const Line& other);

  // Assignment
  Line& operator=(const Line& other);
  void set(const Point& a, const Point& b, bool finite);

  // Comparison
  bool operator==(const Line& other) const;
  bool operator!=(const Line& other) const { return !operator==(other); }

  // Properties
  Point a;
  Point b;
  bool finite;
};

#pragma mark - Inline Implementations

inline Line::Line(const Point& a, const Point& b, bool finite)
    : a(a),
      b(b),
      finite(finite) {}

inline Line::Line(const Line& other)
    : a(other.a),
      b(other.b),
      finite(other.finite) {}

#pragma mark Assignment

inline Line& Line::operator=(const Line& other) {
  if (&other != this) {
    a = other.a;
    b = other.b;
    finite = other.finite;
  }
  return *this;
}

inline void Line::set(const Point& a, const Point& b, bool finite) {
  this->a = a;
  this->b = b;
  this->finite = finite;
}

#pragma mark Comparison

inline bool Line::operator==(const Line &other) const {
  return a == other.a && b == other.b && finite == other.finite;
}

}  // namespace triangulation
}  // namespace takram

#endif  // TAKRAM_TRIANGULATION_LINE_H_
