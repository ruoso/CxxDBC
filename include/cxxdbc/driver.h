#ifndef CXXDBC_DRIVER_H
#define CXXDBC_DRIVER_H

// Include the current version and exposes it syntactically on the
// bare cxxdbc namespace.

#include <cxxdbc/1.0/driver.h>
namespace cxxdbc {
using cxxdbc::v1_0::IDriverImpl;
using cxxdbc::v1_0::Driver;
}

#endif
