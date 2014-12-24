# CxxDBC

C++ Database Connectivity

## About

This project aims to create a general-purpose SQL database abstraction for C++, roughly analogous to JDBC for Java projects.

## Design

### Separate Client and Driver Interfaces

In order to separate the concerns of the end user and the driver developer, CxxDBC provides separate interfaces for each to operate through.

See [API-Versioning.md] for details.

#### Client Object Handles

End users of CxxDBC operate through handles like cxxdbc::Connection. It is intended that these classes:

* contain no surprises
* work for any arbitrary database, provided it has a CxxDBC driver
* provide worry-free lifecycle management
* are value semantic... you can put these things directly in standard library containers
* avoid tight coupling... no inheritance needed

#### Driver Implementation Concept

The driver implementors will mostly be providing classes such that the following works:

```cpp
// In driver-specific code
Connection connection(FoobarDbDriver::Connection("connection:string"));
```

...note that there is no inheritance needed since cxxdbc::Connection uses type erasure. As long as the constructor parameter *looks* like a driver implementation for that class, the above code will compile. The details of how this works is worth reading about, but the upshot is that the handleclasses use compile-time duck typing to interact with actual driver implementations.

For more on type erasure, read [this article](http://www.cplusplus.com/articles/oz18T05o/) or watch [Sean Parent's excellent walkthrough of the pattern](http://channel9.msdn.com/Events/GoingNative/2013/Inheritance-Is-The-Base-Class-of-Evil).

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
