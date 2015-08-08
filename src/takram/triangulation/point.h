//
//  takram/triangulation/point.h
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
#ifndef TAKRAM_TRIANGULATION_POINT_H_
#define TAKRAM_TRIANGULATION_POINT_H_

#include "takram/triangulation/types.h"

namespace takram {
namespace triangulation {

class Point final {
 public:
  Point();

  // Copy semantics
  Point(const Point& other) = default;
  Point& operator=(const Point& other) = default;

  // Implicit conversions
  template <class T>
  Point(const T& other);

  union {
    Vec vector;
    struct { Real x; Real y; };
  };
  int index;
};

#pragma mark -

inline Point::Point() : vector(), index() {}

#pragma mark Implicit conversions

template <class T>
inline Point::Point(const T& other) : vector(other.x, other.y), index() {}

}  // namespace triangulation
}  // namespace takram

#endif  // TAKRAM_TRIANGULATION_POINT_H_
