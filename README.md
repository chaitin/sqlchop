
# SQLChop

[![Build Status](https://travis-ci.org/chaitin/sqlchop.svg?branch=master)](https://travis-ci.org/chaitin/sqlchop)

A novel SQL injection detection engine.

SQLChop is a demo tool of Blackhat 2015 arsenal session. https://www.blackhat.com/us-15/arsenal.html#yusen-chen

## Project homepage

http://sqlchop.chaitin.com

## Demo page

http://sqlchop.chaitin.com/demo

## Description

SQLChop is a novel SQL injection detection engine built on top of SQL tokenizing and syntax analysis. Web input (URLPath, body, cookie, etc.) will be first decoded to the raw payloads that web app accepts, then syntactical analysis will be performed on payload to classify result. The algorithm behind SQLChop is based on compiler knowledge and automata theory, and runs at a time complexity of O(N).

## Documentation

http://sqlchop.chaitin.com/doc.html

## Dependencies

The SQLChop alpha testing release includes the c++ header and shared object, a python library, and also some sample usages. The release has been tested on most linux distributions.

If using python, you need to install `protobuf-python`, e.g.:

```
$ sudo pip install protobuf
```

If using c++, you need to install `protobuf`, `protobuf-compiler` and `protobuf-devel`, e.g.:

```
$ sudo yum install protobuf protobuf-compiler protobuf-devel
```

## Build

 - Download latest release at https://github.com/chaitin/sqlchop/releases
 - Make
 - Run `python2 test.py` or `LD_LIBRARY_PATH=./ ./sqlchop_test`
 - Enjoy!
