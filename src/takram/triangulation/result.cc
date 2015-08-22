//
//  takram/triangulation/result.cc
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

#include "takram/triangulation/result.h"

#include <cstdlib>
#include <cstring>
#include <memory>

#include "takram/triangulation/library.h"

namespace takram {
namespace triangulation {

Result::Result() : data_(std::make_unique<struct triangulateio>()) {
  std::memset(data_.get(), 0, sizeof(*data_));
}

Result::~Result() {
  std::free(data_->pointlist);
  std::free(data_->pointmarkerlist);
  std::free(data_->pointattributelist);
  std::free(data_->trianglelist);
  std::free(data_->triangleattributelist);
  std::free(data_->trianglearealist);
  std::free(data_->neighborlist);
  std::free(data_->segmentlist);
  std::free(data_->segmentmarkerlist);
  std::free(data_->holelist);
  std::free(data_->regionlist);
  std::free(data_->edgelist);
  std::free(data_->edgemarkerlist);
  std::free(data_->normlist);
}

}  // namespace triangulation
}  // namespace takram
