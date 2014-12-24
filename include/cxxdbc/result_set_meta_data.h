#ifndef CXXDBC_RESULTSETMETADATA_H
#define CXXDBC_RESULTSETMETADATA_H

// Include the current version and exposes it syntactically on the
// bare cxxdbc namespace.

#include <cxxdbc/1.0/result_set_meta_data.h>
namespace cxxdbc {
  using cxxdbc::v1_0::IResultSetMetaDataImpl;
  using cxxdbc::v1_0::ResultSetMetaData;
}

#endif
