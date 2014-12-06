# CxxDBC

C++ Database Connectivity

## About

This project aims to create a general-purpose SQL database abstraction for C++, roughly analogous to JDBC for Java projects.

## Getting Started

### Dependencies

* cmake
* Google Test
* C++14

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
