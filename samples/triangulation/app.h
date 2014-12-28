//
//  app.h
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
#ifndef EXAMPLE_APP_H_
#define EXAMPLE_APP_H_

#include <vector>

#include "cinder/Vector.h"

#include "takram/choice.h"
#include "takram/cinder.h"
#include "takram/parameter.h"
#include "takram/triangulation.h"

namespace example {

class App : public takram::cinder::RunnableBase {
 public:
  enum class Type {
    VORONOI,
    DELAUNAY,
    CONSTRAINED_DELAUNAY,
    CONFORMING_DELAUNAY,
    CONSTRAINED_CONFORMING_DELAUNAY
  };

  // Constructors
  App();

  // Framework methods
  void update() override;
  void draw() override;
  void reshape(const ci::Area& viewport) override;
  void mouseDown(const takram::cinder::MouseEvent& event) override;
  void mouseDrag(const takram::cinder::MouseEvent& event) override;

  // List of parameter groups
  takram::ParameterGroups exposeParameters() override;

  // Callback for changes in parameters
  void parameterChange(const takram::ParameterBase& parameter) override;

 private:
  // Data members
  std::vector<ci::Vec2f> points_;
  takram::VoronoiTriangulator voronoi_;
  takram::DelaunayTriangulator delaunay_;
  ci::Vec2i size_;
  bool needs_triangulation_;

  // Parameters
  takram::ParameterT<takram::MappedChoice> type_;
  takram::NumericParameterT<double> min_angle_;
  takram::NumericParameterT<double> max_area_;
  takram::NumericParameterT<int> max_steiner_points_;
  takram::NumericParameterT<bool> uses_min_angle_;
  takram::NumericParameterT<bool> uses_max_area_;
  takram::NumericParameterT<bool> uses_max_steiner_points_;
  takram::NumericParameterT<bool> clear_;
  takram::NumericParameterT<bool> random_;
};

}  // namespace example

#endif  // EXAMPLE_APP_H_
