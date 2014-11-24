//
//  AppDelegate.m
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
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRETDE OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNETDE FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.
//

#if __has_feature(objc_arc)
#error This file must be compiled without ARC. Use -fno-objc-arc flag.
#endif

#import "AppDelegate.h"

#include "example.h"

@interface AppDelegate () {
 @private
  Example _example;
}

@property (nonatomic, assign) IBOutlet NSWindow *window;

@end

@implementation AppDelegate

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:
    (NSApplication *)sender {
  return YES;
}

#pragma mark TDECinderViewDelegate

- (void)cinderViewSetup:(TDECinderView *)cinderView {
  _example.setup();
}

- (void)cinderViewUpdate:(TDECinderView *)cinderView {
  _example.update();
}

- (void)cinderViewDraw:(TDECinderView *)cinderView {
  _example.draw();
}

- (void)cinderView:(TDECinderView *)cinderView
           reshape:(TDECinderAreaRef)viewport {
  _example.reshape(*takram::opaque_cast(viewport));
}

- (void)cinderView:(TDECinderView *)cinderView
           keyDown:(TDECinderKeyEventRef)event {
  _example.keyDown(*takram::opaque_cast(event));
}

- (void)cinderView:(TDECinderView *)cinderView
             keyUp:(TDECinderKeyEventRef)event {
  _example.keyUp(*takram::opaque_cast(event));
}

- (void)cinderView:(TDECinderView *)cinderView
         mouseDown:(TDECinderMouseEventRef)event {
  _example.mouseDown(*takram::opaque_cast(event));
}

- (void)cinderView:(TDECinderView *)cinderView
           mouseUp:(TDECinderMouseEventRef)event {
  _example.mouseUp(*takram::opaque_cast(event));
}

- (void)cinderView:(TDECinderView *)cinderView
         mouseDrag:(TDECinderMouseEventRef)event {
  _example.mouseDrag(*takram::opaque_cast(event));
}

- (void)cinderView:(TDECinderView *)cinderView
         mouseMove:(TDECinderMouseEventRef)event {
  _example.mouseMove(*takram::opaque_cast(event));
}

- (void)cinderView:(TDECinderView *)cinderView
        mouseWheel:(TDECinderMouseEventRef)event {
  _example.mouseWheel(*takram::opaque_cast(event));
}

- (void)cinderView:(TDECinderView *)cinderView
      touchesBegin:(TDECinderTouchEventRef)event {
  _example.touchesBegin(*takram::opaque_cast(event));
}

- (void)cinderView:(TDECinderView *)cinderView
       touchesMove:(TDECinderTouchEventRef)event {
  _example.touchesMove(*takram::opaque_cast(event));
}

- (void)cinderView:(TDECinderView *)cinderView
        touchesEnd:(TDECinderTouchEventRef)event {
  _example.touchesEnd(*takram::opaque_cast(event));
}

- (void)cinderView:(TDECinderView *)cinderView
          fileDrop:(TDECinderFileDropEventRef)event {
  _example.fileDrop(*takram::opaque_cast(event));
}

@end
