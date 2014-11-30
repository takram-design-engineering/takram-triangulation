//
//  takram/triangulation/voronoi_triangulator.h
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
#ifndef TAKRAM_TRIANGULATION_VORONOI_TRIANGULATOR_H_
#define TAKRAM_TRIANGULATION_VORONOI_TRIANGULATOR_H_

#include <memory>
#include <vector>

#include "takram/triangulation/triangulator_base.h"

struct triangulateio;

namespace takram {
namespace triangulation {

class LineIterator;

class VoronoiTriangulator : public TriangulatorBase {
 public:
  // Constructors
  VoronoiTriangulator() {}
  VoronoiTriangulator(const VoronoiTriangulator& other);

  // Assignment
  VoronoiTriangulator& operator=(const VoronoiTriangulator& other);

  // Performing triangulation
  template <typename Vec2>
  bool operator()(const std::vector<Vec2>& points);
  bool operator()(const std::vector<double>& points) override;

  // Iterators
  LineIterator begin() const;
  LineIterator end() const;
};

#pragma mark - Inline Implementations

inline VoronoiTriangulator::VoronoiTriangulator(
    const VoronoiTriangulator& other)
    : TriangulatorBase(other) {}

#pragma mark Assignment

inline VoronoiTriangulator& VoronoiTriangulator::operator=(
    const VoronoiTriangulator& other) {
  TriangulatorBase::operator=(other);
  return *this;
}

#pragma mark Functional operators

template <typename Vec2>
inline bool VoronoiTriangulator::operator()(const std::vector<Vec2>& points) {
  return TriangulatorBase::operator()<Vec2>(points);
}

}  // namespace triangulation
}  // namespace takram

#endif  // TAKRAM_TRIANGULATION_VORONOI_TRIANGULATOR_H_
