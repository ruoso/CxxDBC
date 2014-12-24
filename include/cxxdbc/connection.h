#ifndef CXXDBC_CONNECTION_H
#define CXXDBC_CONNECTION_H

// Include the current version and exposes it syntactically on the
// bare cxxdbc namespace.

#include <cxxdbc/1.0/connection.h>
namespace cxxdbc {
  using cxxdbc::v1_0::IConnectionImpl;
  using cxxdbc::v1_0::Connection;
}

#endif
