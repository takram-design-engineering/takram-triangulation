//
//  takram/triangulation/triangle.h
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
#ifndef TAKRAM_TRIANGULATION_TRIANGLE_H_
#define TAKRAM_TRIANGULATION_TRIANGLE_H_

#include "takram/triangulation/point.h"

namespace takram {
namespace triangulation {

class Triangle final {
 public:
  // Constructors
  Triangle() {}
  Triangle(const Point& a, const Point& b, const Point& c);
  Triangle(const Triangle& other);

  // Assignment
  Triangle& operator=(const Triangle& other);
  void set(const Point& a, const Point& b, const Point& c);

  // Comparison
  bool operator==(const Triangle& other) const;
  bool operator!=(const Triangle& other) const { return !operator==(other); }

  // Properties
  Point& a() { return a_; }
  const Point& a() const { return a_; }
  void set_a(const Point& value) { a_ = value; }
  Point& b() { return b_; }
  const Point& b() const { return b_; }
  void set_b(const Point& value) { b_ = value; }
  Point& c() { return c_; }
  const Point& c() const { return c_; }
  void set_c(const Point& value) { c_ = value; }

 private:
  // Data members
  Point a_;
  Point b_;
  Point c_;
};

#pragma mark - Inline Implementations

inline Triangle::Triangle(const Point& a, const Point& b, const Point& c)
    : a_(a),
      b_(b),
      c_(c) {}

inline Triangle::Triangle(const Triangle& other)
    : a_(other.a_),
      b_(other.b_),
      c_(other.c_) {}

#pragma mark Assignment

inline Triangle& Triangle::operator=(const Triangle& other) {
  if (&other != this) {
    a_ = other.a_;
    b_ = other.b_;
    c_ = other.c_;
  }
  return *this;
}

inline void Triangle::set(const Point& a, const Point& b, const Point& c) {
  a_ = a;
  b_ = b;
  c_ = c;
}

#pragma mark Comparison

inline bool Triangle::operator==(const Triangle &other) const {
  return a_ == other.a_ && b_ == other.b_ && c_ == other.c_;
}

}  // namespace triangulation
}  // namespace takram

#endif  // TAKRAM_TRIANGULATION_TRIANGLE_H_
