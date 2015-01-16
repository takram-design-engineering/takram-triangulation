//
//  takram/triangulation/triangle_iterator.h
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
#ifndef TAKRAM_TRIANGULATION_TRIANGLE_ITERATOR_H_
#define TAKRAM_TRIANGULATION_TRIANGLE_ITERATOR_H_

#include <iterator>

#include "takram/triangulation/triangle.h"
#include "takram/triangulation/delaunay_triangulator.h"

namespace takram {
namespace triangulation {

class TriangleIterator final : public std::iterator<
    std::forward_iterator_tag,
    const Triangle> {
 public:
  // Constructors
  TriangleIterator();
  TriangleIterator(const int *triangles, const double *points);
  TriangleIterator(const TriangleIterator& other) = default;

  // Assignment
  TriangleIterator& operator=(const TriangleIterator& other) = default;

  // Comparison
  bool operator==(const TriangleIterator& other) const;
  bool operator!=(const TriangleIterator& other) const;

  // Operators
  const Triangle& operator*() const;
  const Triangle * operator->() const { return &operator*(); }
  TriangleIterator& operator++();
  TriangleIterator operator++(int);

 private:
  // Data members
  const int *triangles_;
  const double *points_;
  mutable const int *current_triangle_;
  mutable Triangle derived_triangle_;
};

#pragma mark - Inline Implementations

inline TriangleIterator::TriangleIterator()
    : triangles_(nullptr),
      points_(nullptr),
      current_triangle_(nullptr) {}

inline TriangleIterator::TriangleIterator(const int *triangles,
                                          const double *points)
    : triangles_(triangles),
      points_(points),
      current_triangle_(nullptr) {}

#pragma mark Comparison

inline bool TriangleIterator::operator==(const TriangleIterator& other) const {
  return triangles_ == other.triangles_;
}

inline bool TriangleIterator::operator!=(const TriangleIterator& other) const {
  return !operator==(other);
}

#pragma mark Operators

inline TriangleIterator& TriangleIterator::operator++() {
  if (triangles_) {
    triangles_ += 3;
  }
  return *this;
}

inline TriangleIterator TriangleIterator::operator++(int) {
  TriangleIterator result(*this);
  operator++();
  return result;
}

}  // namespace triangulation
}  // namespace takram

#endif  // TAKRAM_TRIANGULATION_TRIANGLE_ITERATOR_H_
