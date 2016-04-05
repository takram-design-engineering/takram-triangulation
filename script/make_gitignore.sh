#!/bin/sh
#
#  make_gitignore.sh
#
#  The MIT License
#
#  Copyright (C) 2014-2015 Shota Matsuda
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

readonly PROJECT_DIR="$(cd "$(dirname "$0")/../"; pwd)"
readonly FILES=("Global/OSX" "Global/Windows" "Global/Xcode" "VisualStudio")

repository_dir=$(mktemp -d -t "com.takram.gitignore")

concat_gitignore() {
  for file in "${FILES[@]}"; do
    echo "# https://github.com/github/gitignore/blob/master/${file}.gitignore"
    echo ""
    cat "${repository_dir}/${file}.gitignore"
    echo ""
  done
}

git clone "https://github.com/github/gitignore.git" "${repository_dir}"
concat_gitignore > "${PROJECT_DIR}/.gitignore"
rm -rf "${repository_dir}"
