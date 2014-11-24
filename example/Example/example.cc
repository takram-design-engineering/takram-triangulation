//
//  example.cc
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

#include "example.h"

#include <cstdint>
#include <vector>

#include "cinder/Color.h"
#include "cinder/gl/gl.h"

#include "takram/triangulation.h"

void Example::setup() {
  // Inside OpenGL context.
  // Write your setup codes here.
}

void Example::update() {
  // Outside OpenGL context and in a background thread.
  // Write your non-drawing codes here as much as possible to reduce load of
  // the UI thread.
}

void Example::draw() {
  // Inside OpenGL context.
  // Write your drawing codes here.

  ci::gl::clear(ci::Color::white());
  ci::gl::enableAlphaBlending();
  ci::gl::pushMatrices();
  ci::gl::color(ci::Color::black());
  for (const auto& point : points_) {
    ci::gl::drawSolidCircle(point, 2.0);
  }
  ci::gl::color(ci::ColorA(0.0, 0.0, 0.0, 0.5));
  ci::gl::draw(ci::PolyLine2f(points_));
  if (!triangle_mesh_ && points_.size() >= 3) {
    takram::Triangulation triangulation;
    triangulation(points_);
    std::vector<ci::Vec3f> positions;
    std::vector<std::uint32_t> indices;
    std::uint32_t index = 0;
    for (const auto& triangle : triangulation) {
      positions.emplace_back(triangle.a().x(), triangle.a().y(), 0.0);
      positions.emplace_back(triangle.b().x(), triangle.b().y(), 0.0);
      positions.emplace_back(triangle.b().x(), triangle.b().y(), 0.0);
      positions.emplace_back(triangle.c().x(), triangle.c().y(), 0.0);
      positions.emplace_back(triangle.c().x(), triangle.c().y(), 0.0);
      positions.emplace_back(triangle.a().x(), triangle.a().y(), 0.0);
      indices.emplace_back(index++);
      indices.emplace_back(index++);
      indices.emplace_back(index++);
      indices.emplace_back(index++);
      indices.emplace_back(index++);
      indices.emplace_back(index++);
    }
    ci::gl::VboMesh::Layout layout;
    layout.setStaticPositions();
    layout.setStaticIndices();
    triangle_mesh_ = ci::gl::VboMesh(
        positions.size(),
        indices.size(),
        layout,
        GL_LINES);
    triangle_mesh_.bufferPositions(positions);
    triangle_mesh_.bufferIndices(indices);
  }
  if (triangle_mesh_) {
    ci::gl::color(ci::ColorA(0.0, 0.0, 0.0, 0.1));
    ci::gl::draw(triangle_mesh_);
  }
  ci::gl::popMatrices();
}

void Example::reshape(const ci::Area& viewport) {
  // Inside OpenGL context.
  // Called when the cinder view's visible rectangle or bounds change.
  // Adjust the viewport and display frustum here if you need.
}

void Example::keyDown(const ci::app::KeyEvent& event) {
  // Outside OpenGL context.
}

void Example::keyUp(const ci::app::KeyEvent& event) {
  // Outside OpenGL context.
}

void Example::mouseDown(const takram::cinder::MouseEvent& event) {
  // Outside OpenGL context.
  points_.emplace_back(event.getX(), event.getY());
  triangle_mesh_.reset();
}

void Example::mouseUp(const takram::cinder::MouseEvent& event) {
  // Outside OpenGL context.
}

void Example::mouseDrag(const takram::cinder::MouseEvent& event) {
  // Outside OpenGL context.
  points_.emplace_back(event.getX(), event.getY());
  triangle_mesh_.reset();
}

void Example::mouseMove(const takram::cinder::MouseEvent& event) {
  // Outside OpenGL context.
}

void Example::mouseWheel(const takram::cinder::MouseEvent& event) {
  // Outside OpenGL context.
}

void Example::touchesBegin(const takram::cinder::TouchEvent& event) {
  // Outside OpenGL context.
}

void Example::touchesMove(const takram::cinder::TouchEvent& event) {
  // Outside OpenGL context.
}

void Example::touchesEnd(const takram::cinder::TouchEvent& event) {
  // Outside OpenGL context.
}

void Example::fileDrop(const ci::app::FileDropEvent& event) {
  // Outside OpenGL context.
}
