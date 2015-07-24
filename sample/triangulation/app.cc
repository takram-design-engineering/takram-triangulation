//
//  app.cc
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

#include "app.h"

#include <cassert>
#include <limits>
#include <random>
#include <utility>
#include <vector>

#include "cinder/Color.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"

#include "takram/cinder.h"
#include "takram/parameter.h"
#include "takram/triangulation.h"

namespace example {

App::App()
    : needs_triangulation_(false),
      type_("Type"),
      min_angle_("Min Angle", 20.0, 0.0, 20.0),
      max_area_("Max Area", 100.0, 100.0, 10000.0),
      max_steiner_points_("Max Steiner Points", 0, 0, 10000),
      uses_min_angle_("Use Min Angle", false),
      uses_max_area_("Use Max Area", false),
      uses_max_steiner_points_("Use Max Steiner Points", false),
      clear_("Clear"),
      random_("Random") {
  type_->set_options({
    std::make_pair(Type::VORONOI, "Voronoi"),
    std::make_pair(Type::DELAUNAY, "Delaunay"),
    std::make_pair(Type::CONSTRAINED_DELAUNAY, "Constrained Delaunay"),
    std::make_pair(Type::CONFORMING_DELAUNAY, "Conforming Delaunay"),
    std::make_pair(Type::CONSTRAINED_CONFORMING_DELAUNAY,
                   "Constrained Conforming Delaunay")
  });
  type_->set_allows_multiple(false);
  type_->set_allows_empty(false);
  type_.set_preferred_interface(takram::Parameter::Interface::POPUP_BUTTON);
  clear_.set_preferred_interface(takram::NumericParameter::Interface::BUTTON);
  random_.set_preferred_interface(takram::NumericParameter::Interface::BUTTON);
}

void App::update() {
  if (needs_triangulation_ && points_.size() > 2) {
    takram::Triangulator *triangulator;
    if (type_->has(Type::VORONOI)) {
      triangulator = &voronoi_;
    } else {
      triangulator = &delaunay_;
      using DelaunayType = takram::DelaunayTriangulator::Type;
      if (type_->has(Type::DELAUNAY)) {
        delaunay_.set_type(DelaunayType::DEFAULT);
      } else if (type_->has(Type::CONSTRAINED_DELAUNAY)) {
        delaunay_.set_type(DelaunayType::CONSTRAINED);
      } else if (type_->has(Type::CONFORMING_DELAUNAY)) {
        delaunay_.set_type(DelaunayType::CONFORMING);
      } else if (type_->has(Type::CONSTRAINED_CONFORMING_DELAUNAY)) {
        delaunay_.set_type(DelaunayType::CONSTRAINED_CONFORMING);
      } else {
        assert(false);
      }
    }
    if (uses_min_angle_) {
      triangulator->set_min_angle(min_angle_);
    } else {
      triangulator->set_min_angle(std::numeric_limits<double>::quiet_NaN());
    }
    if (uses_max_area_) {
      triangulator->set_max_area(max_area_);
    } else {
      triangulator->set_max_area(std::numeric_limits<double>::quiet_NaN());
    }
    if (uses_max_steiner_points_) {
      triangulator->set_max_steiner_points(max_steiner_points_);
    } else {
      triangulator->set_max_steiner_points(-1);
    }
    (*triangulator)(points_);
    needs_triangulation_ = false;
  }
}

void App::draw() {
  ci::gl::clear(ci::Color::white());
  if (type_->has(Type::VORONOI)) {
    const auto diagonal = ci::gl::getViewport().getSize().length();
    ci::Vec2f a, b;
    ci::gl::color(ci::ColorA(0.0, 0.0, 0.0, 0.2));
    for (const auto& line : voronoi_) {
      a.set(line.a.x, line.a.y);
      if (line.finite) {
        b.set(line.b.x, line.b.y);
      } else {
        const auto normal = ci::Vec2d(line.b.x, line.b.y).normalized();
        b.set(line.a.x + normal.x * diagonal, line.a.y + normal.y * diagonal);
      }
      ci::gl::drawLine(a, b);
    }
  } else {
    ci::Vec2f a, b, c;
    ci::gl::color(ci::ColorA(0.0, 0.0, 0.0, 0.1));
    for (const auto& triangle : delaunay_) {
      a.set(triangle.a.x, triangle.a.y);
      b.set(triangle.b.x, triangle.b.y);
      c.set(triangle.c.x, triangle.c.y);
      ci::gl::drawLine(a, b);
      ci::gl::drawLine(b, c);
      ci::gl::drawLine(c, a);
    }
  }
  ci::gl::color(ci::Color::black());
  for (const auto& point : points_) {
    ci::gl::drawSolidCircle(point, 2.0);
  }
}

void App::reshape(const ci::Area& viewport) {
  ci::gl::setMatricesWindow(viewport.getWidth(), viewport.getHeight());
  size_ = viewport.getSize();
}

void App::mouseDown(const takram::cinder::MouseEvent& event) {
  points_.emplace_back(event.getX(), event.getY());
  needs_triangulation_ = true;
}

void App::mouseDrag(const takram::cinder::MouseEvent& event) {
  points_.emplace_back(event.getX(), event.getY());
  needs_triangulation_ = true;
}

takram::ParameterGroups App::exposeParameters() {
  return takram::ParameterGroups{
    std::make_pair("Triangulation", takram::Parameters{
      &type_,
      &min_angle_,
      &max_area_,
      &max_steiner_points_,
      &uses_min_angle_,
      &uses_max_area_,
      &uses_max_steiner_points_,
      &clear_,
      &random_
    })
  };
}

void App::parameterChange(const takram::ParameterBase& parameter) {
  if (&parameter == &clear_) {
    points_.clear();
    voronoi_.clear();
    delaunay_.clear();
  } else if (&parameter == &random_) {
    std::random_device random_device;
    std::default_random_engine engine(random_device());
    std::uniform_int_distribution<> x_distribution(0, size_.x);
    std::uniform_int_distribution<> y_distribution(0, size_.y);
    for (int i = 0, n = size_.x * size_.y / 10000; i < n; ++i) {
      points_.emplace_back(x_distribution(engine), y_distribution(engine));
    }
  }
  needs_triangulation_ = true;
}

}  // namespace example
