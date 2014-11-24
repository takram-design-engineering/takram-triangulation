//
//  takram/triangulation/triangle_iterator.cc
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

#include "takram/triangulation/triangle_iterator.h"

#include "takram/triangulation/point.h"

namespace takram {
namespace triangulation {

#pragma mark Operators

const Triangle& TriangleIterator::operator*() const {
  if (current_triangle_ != triangles_) {
    const int a = *(triangles_ + 0) * 2;
    const int b = *(triangles_ + 1) * 2;
    const int c = *(triangles_ + 2) * 2;
    derived_triangle_.set(Point(points_ + a),
                          Point(points_ + b),
                          Point(points_ + c));
    current_triangle_ = triangles_;
  }
  return derived_triangle_;
}

TriangleIterator& TriangleIterator::operator++() {
  if (triangles_) {
    triangles_ += 3;
  }
  return *this;
}

}  // namespace triangulation
}  // namespace takram
