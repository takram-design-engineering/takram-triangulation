//
//  takram/triangulation/edge_iterator.h
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
#ifndef TAKRAM_TRIANGULATION_EDGE_ITERATOR_H_
#define TAKRAM_TRIANGULATION_EDGE_ITERATOR_H_

#include <iterator>
#include <memory>

#include "takram/triangulation/edge.h"
#include "takram/triangulation/result.h"

struct triangulateio;

namespace takram {
namespace triangulation {

class EdgeIterator final
    : public std::iterator<std::forward_iterator_tag, const Edge> {
 public:
  EdgeIterator();
  explicit EdgeIterator(const std::shared_ptr<Result>& result);
  EdgeIterator(const std::shared_ptr<Result>& result, const int *current);

  // Copy semantics
  EdgeIterator(const EdgeIterator& other) = default;
  EdgeIterator& operator=(const EdgeIterator& other) = default;

  // Comparison
  bool operator==(const EdgeIterator& other) const;
  bool operator!=(const EdgeIterator& other) const;

  // Iterator
  const Edge& operator*() const;
  const Edge * operator->() const { return &operator*(); }
  EdgeIterator& operator++();
  EdgeIterator operator++(int);

 private:
  std::shared_ptr<Result> result_;
  const int * const begin_;
  const int *current_;

  // Cache
  mutable const int *derived_;
  mutable Edge edge_;
};

#pragma mark -

inline EdgeIterator::EdgeIterator() : begin_(), current_(), derived_() {}

#pragma mark Comparison

inline bool EdgeIterator::operator==(const EdgeIterator& other) const {
  return current_ == other.current_;
}

inline bool EdgeIterator::operator!=(const EdgeIterator& other) const {
  return !operator==(other);
}

#pragma mark Iterator

inline EdgeIterator& EdgeIterator::operator++() {
  current_ += 2;
  return *this;
}

inline EdgeIterator EdgeIterator::operator++(int) {
  EdgeIterator result(*this);
  operator++();
  return result;
}

}  // namespace triangulation
}  // namespace takram

#endif  // TAKRAM_TRIANGULATION_EDGE_ITERATOR_H_
