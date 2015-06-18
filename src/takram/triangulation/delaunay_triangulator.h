//
//  takram/triangulation/delaunay_triangulator.h
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
#ifndef TAKRAM_TRIANGULATION_DELAUNAY_TRIANGULATOR_H_
#define TAKRAM_TRIANGULATION_DELAUNAY_TRIANGULATOR_H_

#include <cstddef>
#include <vector>

#include "takram/triangulation/triangle_iterator.h"
#include "takram/triangulation/triangulator.h"
#include "takram/triangulation/types.h"

namespace takram {
namespace triangulation {

class DelaunayTriangulator : public Triangulator {
 public:
  enum class Type {
    DEFAULT = 0,
    CONSTRAINED,
    CONFORMING,
    CONSTRAINED_CONFORMING
  };

 public:
  DelaunayTriangulator();
  explicit DelaunayTriangulator(Type type);

  // Copy semantics
  DelaunayTriangulator(const DelaunayTriangulator& other) = default;
  DelaunayTriangulator& operator=(const DelaunayTriangulator& other) = default;

  // Triangulation
  using Triangulator::operator();
  bool operator()(const std::vector<Real>& coordinates) override;

  // Parameters
  Type type() const { return type_; }
  void set_type(Type value) { type_ = value; }

  // Attributes
  std::size_t size() const override;

  // Iterator
  TriangleIterator begin() const;
  TriangleIterator end() const;

 private:
  Type type_;
};

#pragma mark -

inline DelaunayTriangulator::DelaunayTriangulator() : type_(Type::DEFAULT) {}

inline DelaunayTriangulator::DelaunayTriangulator(Type type) : type_(type) {}

}  // namespace triangulation
  
using triangulation::DelaunayTriangulator;
  
}  // namespace takram

#endif  // TAKRAM_TRIANGULATION_DELAUNAY_TRIANGULATOR_H_
