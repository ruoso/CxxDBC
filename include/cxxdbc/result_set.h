#ifndef CXXDBC_RESULTSET_H
#define CXXDBC_RESULTSET_H

// Include the current version and exposes it syntactically on the
// bare cxxdbc namespace.

#include <cxxdbc/1.0/result_set.h>
namespace cxxdbc {
  using cxxdbc::v1_0::IResultSetImpl;
  using cxxdbc::v1_0::ResultSet;
}

#endif
