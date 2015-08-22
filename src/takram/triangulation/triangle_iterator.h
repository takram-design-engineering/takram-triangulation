//
//  takram/triangulation/triangle_iterator.h
//
//  The MIT License
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
#ifndef TAKRAM_TRIANGULATION_TRIANGLE_ITERATOR_H_
#define TAKRAM_TRIANGULATION_TRIANGLE_ITERATOR_H_

#include <iterator>
#include <memory>

#include "takram/triangulation/result.h"
#include "takram/triangulation/types.h"

namespace takram {
namespace triangulation {

class TriangleIterator final
    : public std::iterator<std::forward_iterator_tag, const Triangle> {
 public:
  TriangleIterator();
  explicit TriangleIterator(const std::shared_ptr<Result>& result);
  TriangleIterator(const std::shared_ptr<Result>& result, const int *current);

  // Copy semantics
  TriangleIterator(const TriangleIterator&) = default;
  TriangleIterator& operator=(const TriangleIterator&) = default;

  // Comparison
  bool operator==(const TriangleIterator& other) const;
  bool operator!=(const TriangleIterator& other) const;

  // Iterator
  const Triangle& operator*() const;
  const Triangle * operator->() const { return &operator*(); }
  TriangleIterator& operator++();
  TriangleIterator operator++(int);

 private:
  std::shared_ptr<Result> result_;
  const int * const begin_;
  const int *current_;

  // Cache
  mutable const int *derived_;
  mutable Triangle triangle_;
};

#pragma mark -

inline TriangleIterator::TriangleIterator()
    : begin_(),
      current_(),
      derived_() {}

#pragma mark Comparison

inline bool TriangleIterator::operator==(const TriangleIterator& other) const {
  return current_ == other.current_;
}

inline bool TriangleIterator::operator!=(const TriangleIterator& other) const {
  return !operator==(other);
}

#pragma mark Iterator

inline TriangleIterator& TriangleIterator::operator++() {
  current_ += 3;
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
