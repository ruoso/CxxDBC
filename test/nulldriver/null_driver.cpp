#include <memory>
#include "null_driver.h"
#include <cxxdbc/1.0/exception.h>
#include <cxxdbc/1.0/connection.h>
#include <cxxdbc/1.0/concept/connection.h>

namespace cxxdbc {
namespace nulldriver {

class NullConnection {
public:
  void clearWarnings() {
  };
  void close() {
  }
  void commit() {
  };
  bool isClosed() const {
    return 1;
  }
  bool isReadOnly() const {
    return 1;
  }
  void rollback() {
  };
};


bool NullDriver::acceptsURL(boost::string_ref url) const {
  std::string prefix = "null:";
  if (url.length() >= prefix.length())
    return std::equal(prefix.begin(), prefix.end(), url.begin());
  else
    return 0;
}

Connection NullDriver::connect(boost::string_ref url, Properties info) {
  (void)info; // unused;
  if (acceptsURL(url)) {
    NullConnection nc;
    return cxxdbc::v1_0::Connection(std::move(nc));
  } else {
    throw cxxdbc::v1_0::Exception("Unsupported URL");
  }
}

int NullDriver::getMajorVersion() const {
  return 0;
}

int NullDriver::getMinorVersion() const {
  return 0;
}

std::vector<DriverPropertyInfo> NullDriver::getPropertyInfo(boost::string_ref url,
                                                            Properties info) const {
  (void)url; // unused
  (void)info; // unused
  std::vector<DriverPropertyInfo> ret = {};
  return ret;
}

int NullDriver::getSupportedCxxDBCMajorVersion() const {
  return 1;
}

int NullDriver::getSupportedCxxDBCMinorVersion() const {
  return 0;
}

bool NullDriver::isEqual(IDriver const &driver) const {
  return (IDriver*)std::addressof(this) == std::addressof(driver);
}

bool NullDriver::isSQL() const {
  return 1;
}


}
}
