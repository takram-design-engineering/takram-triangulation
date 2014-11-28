#!/bin/sh
#
#  build_glog.sh
#
#  MIT License
#
#  Copyright (C) 2013-2014 Shota Matsuda
#  Copyright (C) 2014 takram design engineering
#
#  Permission is hereby granted, free of charge, to any person obtaining a
#  copy of this software and associated documentation files (the "Software"),
#  to deal in the Software without restriction, including without limitation
#  the rights to use, copy, modify, merge, publish, distribute, sublicense,
#  and/or sell copies of the Software, and to permit persons to whom the
#  Software is furnished to do so, subject to the following conditions:
#
#  The above copyright notice and this permission notice shall be included in
#  all copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
#  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
#  DEALINGS IN THE SOFTWARE.
#

readonly CMAKE=$(which cmake)
readonly CLANG_CC=$(which clang)
readonly CLANG_CXX=$(which clang++)

if [[ ! -f "${CMAKE}" ]]; then
  echo "cmake was not found."
  exit 1
fi
if [[ ! -f "${CLANG_CC}" ]]; then
  echo "clang was not found."
  exit 1
fi
if [[ ! -f "${CLANG_CXX}" ]]; then
  echo "clang++ was not found."
  exit 1
fi

readonly SRCROOT="$(cd "$(dirname "$0")/../"; pwd)"
readonly TARGET_DIR="${SRCROOT}/glog"
readonly TARGET_BUILD_DIR="${SRCROOT}/build/glog"

mkdir -p "${TARGET_BUILD_DIR}"
pushd "${TARGET_BUILD_DIR}"
  "${TARGET_DIR}/configure" --prefix="${TARGET_BUILD_DIR}" \
      CC="${CLANG_CC}" \
      CXX="${CLANG_CXX}" \
      CXXFLAGS="-stdlib=libc++"
  make -j8
  make install
  make clean
popd
