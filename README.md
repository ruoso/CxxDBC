# CxxDBC

C++ Database Connectivity

## About

This project aims to create a general-purpose SQL database abstraction for C++, roughly analogous to JDBC for Java projects.

## Interfaces Semantic Translation

In order to translate usefully the life-cycle semantics of the JDBC
objects, the types that in Java are represented solely by an
interface, in this library are represented by a pair of an purely
virtual class (prefixed with a capital "I") and a concrete class that
manages the life-cycle of the virtual object. This is to allow for an
easier user API with well-defined life-cycle semantics that are
independent of the driver implementation.

## Getting Started

### Dependencies

*Mandatory*
* cmake
* Google Test
* C++14

*Optional*
* clang-format

### To Build

Assuming your work area is in CXXDBC_REPO
```sh
mkdir /tmp/cxxdbc_release
cd /tmp/cxxdbc_release
cmake $CXXDBC_REPO
```

### To Test
```sh
make all test
```
...or...
```sh
make && ./cxxdbc_test
```

### To Format Code
```sh
./bin/format.sh
```
