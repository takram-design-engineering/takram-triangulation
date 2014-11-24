//
//  example.h
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
#ifndef EXAMPLE_H_
#define EXAMPLE_H_

#include <vector>

#include "cinder/app/App.h"
#include "cinder/gl/Vbo.h"
#include "cinder/Vector.h"
#include "takram/cinder.h"

class Example {
 public:
  // Framework methods
  void setup();
  void update();
  void draw();
  void reshape(const ci::Area& viewport);
  void keyDown(const ci::app::KeyEvent& event);
  void keyUp(const ci::app::KeyEvent& event);
  void mouseDown(const takram::cinder::MouseEvent& event);
  void mouseUp(const takram::cinder::MouseEvent& event);
  void mouseDrag(const takram::cinder::MouseEvent& event);
  void mouseMove(const takram::cinder::MouseEvent& event);
  void mouseWheel(const takram::cinder::MouseEvent& event);
  void touchesBegin(const takram::cinder::TouchEvent& event);
  void touchesMove(const takram::cinder::TouchEvent& event);
  void touchesEnd(const takram::cinder::TouchEvent& event);
  void fileDrop(const ci::app::FileDropEvent& event);

 private:
  // Data members
  std::vector<ci::Vec2f> points_;
  ci::gl::VboMesh triangle_mesh_;
};

#endif  // EXAMPLE_H_
