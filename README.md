Triangulation
=============

## Dependencies

### Libraries

- [glog](https://code.google.com/p/google-glog/)
- [triangle](http://www.cs.cmu.edu/~quake/triangle.html)

Install those via [Homebrew](http://brew.sh) on OS X:

```
$ brew install glog
$ brew install triangle
```

### Submodules

- [googletest](https://github.com/sgss/mirror-googletest)
- [cinder](https://github.com/cinder/Cinder)
- [cpplint](https://github.com/sgss/mirror-cpplint)

Don't forget to initialize submodules:

```
$ git submodule update --init --recursive
```

Then build googletest by running the script:

```
$ scripts/build_googletest.sh
```

## Style Guide

This project tries to conform to [Google's C++ Style Guide](http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml) except:

- Use of lambda expressions
- Use of exceptions in exceptional cases
- Use of streams when strongly needed for convenience

## License

MIT License

Copyright (C) 2014 takram design engineering

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
