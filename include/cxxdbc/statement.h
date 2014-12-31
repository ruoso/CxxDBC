#ifndef CXXDBC_STATEMENT_H
#define CXXDBC_STATEMENT_H

// Include the current version and exposes it syntactically on the
// bare cxxdbc namespace.

#include <cxxdbc/1.0/statement.h>
namespace cxxdbc {
using cxxdbc::v1_0::IStatementImpl;
using cxxdbc::v1_0::Statement;
}

#endif
