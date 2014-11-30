//
//  takram/triangulation/line_iterator.h
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
#ifndef TAKRAM_TRIANGULATION_LINE_ITERATOR_H_
#define TAKRAM_TRIANGULATION_LINE_ITERATOR_H_

#include <cstddef>
#include <iterator>

#include "takram/triangulation/line.h"
#include "takram/triangulation/voronoi_triangulator.h"

namespace takram {
namespace triangulation {

class LineIterator final : public std::iterator<
    std::forward_iterator_tag,
    const Line> {
 public:
  // Constructors
  LineIterator();
  LineIterator(const int *edges,
               const double *points,
               const double *normals);
  LineIterator(const LineIterator& other);

  // Assignment
  LineIterator& operator=(const LineIterator& other);

  // Comparison
  bool operator==(const LineIterator& other) const;
  bool operator!=(const LineIterator& other) const;

  // Operators
  const Line& operator*() const;
  const Line * operator->() const { return &operator*(); }
  LineIterator& operator++();
  LineIterator operator++(int);

 private:
  // Data members
  const int *edges_;
  const double *points_;
  const double *normals_;
  mutable const int *current_edge_;
  mutable Line derived_line_;
};

#pragma mark - Inline Implementations

inline LineIterator::LineIterator()
    : edges_(nullptr),
      points_(nullptr),
      current_edge_(nullptr) {}

inline LineIterator::LineIterator(const int *edges,
                                  const double *points,
                                  const double *normals)
    : edges_(edges),
      points_(points),
      normals_(normals),
      current_edge_(nullptr) {}

inline LineIterator::LineIterator(const LineIterator& other)
    : edges_(other.edges_),
      points_(other.points_),
      normals_(other.normals_),
      current_edge_(other.current_edge_),
      derived_line_(other.derived_line_) {}

#pragma mark Assignment

inline LineIterator& LineIterator::operator=(const LineIterator& other) {
  if (&other != this) {
    edges_ = other.edges_;
    points_ = other.points_;
    normals_ = other.normals_;
    current_edge_ = other.current_edge_;
    derived_line_ = other.derived_line_;
  }
  return *this;
}

#pragma mark Comparison

inline bool LineIterator::operator==(const LineIterator& other) const {
  return edges_ == other.edges_;
}

inline bool LineIterator::operator!=(const LineIterator& other) const {
  return !operator==(other);
}

#pragma mark Operators

inline LineIterator LineIterator::operator++(int) {
  LineIterator result(*this);
  operator++();
  return result;
}

}  // namespace triangulation
}  // namespace takram

#endif  // TAKRAM_TRIANGULATION_LINE_ITERATOR_H_
