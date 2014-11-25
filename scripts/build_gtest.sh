#!/bin/sh
#
#  build_gtest.sh
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
readonly GTEST_DIR="${SRCROOT}/gtest"
readonly GTEST_BUILD_DIR="${GTEST_DIR}/build"

mkdir -p "${GTEST_BUILD_DIR}"
pushd "${GTEST_BUILD_DIR}"
  "${CMAKE}" -G "Unix Makefiles" \
      -DCMAKE_BUILD_TYPE="RELEASE" \
      -DCMAKE_C_COMPILER="${CLANG_CC}" \
      -DCMAKE_CXX_COMPILER="${CLANG_CXX}" \
      -DCMAKE_CXX_FLAGS="-stdlib=libc++" \
      -DCMAKE_OSX_ARCHITECTURES="i386;x86_64" \
      "${GTEST_DIR}"
  make -j8
popd
