//
//  takram/triangulation/delaunay_triangulator.h
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
#ifndef TAKRAM_TRIANGULATION_DELAUNAY_TRIANGULATOR_H_
#define TAKRAM_TRIANGULATION_DELAUNAY_TRIANGULATOR_H_

#include <memory>
#include <vector>

#include "takram/triangulation/triangulator_base.h"

struct triangulateio;

namespace takram {
namespace triangulation {

class TriangleIterator;

class DelaunayTriangulator : public TriangulatorBase {
 public:
  enum class Type {
    DEFAULT = 0,
    CONSTRAINED,
    CONFORMING,
    CONFORMING_CONSTRAINED
  };

  // Constructors
  DelaunayTriangulator();
  explicit DelaunayTriangulator(Type type);
  DelaunayTriangulator(const DelaunayTriangulator& other);

  // Assignment
  DelaunayTriangulator& operator=(const DelaunayTriangulator& other);

  // Performing triangulation
  template <typename Vec2>
  bool operator()(const std::vector<Vec2>& points);
  bool operator()(const std::vector<double>& points) override;

  // Parameters
  Type type() const { return type_; }
  void set_type(Type value) { type_ = value; }

  // Iterators
  TriangleIterator begin() const;
  TriangleIterator end() const;

 private:
  // Data members
  Type type_;
};

#pragma mark - Inline Implementations

inline DelaunayTriangulator::DelaunayTriangulator()
    : TriangulatorBase(),
      type_(Type::DEFAULT) {}

inline DelaunayTriangulator::DelaunayTriangulator(Type type)
    : TriangulatorBase(),
      type_(type) {}

inline DelaunayTriangulator::DelaunayTriangulator(
    const DelaunayTriangulator& other)
    : TriangulatorBase(other),
      type_(other.type_) {}

#pragma mark Assignment

inline DelaunayTriangulator& DelaunayTriangulator::operator=(
    const DelaunayTriangulator& other) {
  TriangulatorBase::operator=(other);
  if (&other != this) {
    type_ = other.type_;
  }
  return *this;
}

#pragma mark Functional operators

template <typename Vec2>
inline bool DelaunayTriangulator::operator()(const std::vector<Vec2>& points) {
  return TriangulatorBase::operator()<Vec2>(points);
}

}  // namespace triangulation
}  // namespace takram

#endif  // TAKRAM_TRIANGULATION_DELAUNAY_TRIANGULATOR_H_
