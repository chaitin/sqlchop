
# SQLChop

A novol SQL injection detection engine.

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

The current alpha testing release is provided as a python library. C++ headers and examples will be released soon.

To install `protobuf-python`, you can use `pip`, `easy_install` or `pacman`, `yum`, `apt-get` as needed.

```
$ sudo pip install protobuf
```

## Build

 - Download latest release at https://github.com/chaitin/sqlchop/releases
 - make
 - run test.py
 - Enjoy!
