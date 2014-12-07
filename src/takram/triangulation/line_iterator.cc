//
//  takram/triangulation/line_iterator.cc
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

#include "takram/triangulation/line_iterator.h"

#include "takram/triangulation/line.h"
#include "takram/triangulation/point.h"

namespace takram {
namespace triangulation {

#pragma mark Operators

const Line& LineIterator::operator*() const {
  if (current_edge_ != edges_) {
    const int a = *(edges_ + 0) * 2;
    const int b = *(edges_ + 1) * 2;
    if (b < 0) {
      derived_line_.set(Point(points_ + a), Point(normals_), false);
    } else {
      derived_line_.set(Point(points_ + a), Point(points_ + b), true);
    }
    current_edge_ = edges_;
  }
  return derived_line_;
}

}  // namespace triangulation
}  // namespace takram
