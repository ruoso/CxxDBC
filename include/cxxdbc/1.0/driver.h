#ifndef INCLUDED_CXXDBC_1_0_DRIVER_H
#define INCLUDED_CXXDBC_1_0_DRIVER_H

// third-party includes
#include <boost/utility/string_ref.hpp>

// cxxdbc includes
#include <cxxdbc/1.0/driver_property_info.h>
#include <cxxdbc/1.0/properties.h>
#include <cxxdbc/1.0/connection.h>

// standard includes
#include <memory>

namespace cxxdbc {
namespace v1_0 {

/// Defines the v-table for dynamic dispatch to a driver implementation of the driver concept.
class IDriver {
public:  // RAII
  virtual ~IDriver() = default;

public:  // methods
  virtual bool acceptsURL(boost::string_ref url);
  virtual Connection connect(boost::string_ref url,
                             Properties info);
  virtual std::vector<DriverPropertyInfo> getPropertyInfo(boost::string_ref url,
                                                          Properties info);
  // is this a regular SQL driver?
  virtual int isSQL();
  // Version of the driver itself
  virtual int getMajorVersion();
  virtual int getMinorVersion();
  // Version of the CxxDBC API implemented by the driver
  virtual int getSupportedCxxDBCMajorVersion();
  virtual int getSupportedCxxDBCMinorVersion();
};

/// A handle to a driver
class Driver {
private:  // variables
  // a driver handle can actually be held by several people
  // at once. So we use shared_ptr instead of unique_ptr.
  ::std::shared_ptr<IDriver> m_driver;

public:  // RAII
  Driver() = default;

  Driver(const Driver &) = default;

  Driver(Driver &&) = default;

  explicit Driver(::std::shared_ptr<IDriver> &&driver)
    : m_driver(driver) {}

  ~Driver() {}

public:  // methods
  bool acceptsURL(boost::string_ref url) {
    return m_driver->acceptsURL(url);
  }
  Connection connect(boost::string_ref url,
                     Properties info) {
    return m_driver->connect(url, info);
  }
  std::vector<DriverPropertyInfo> getPropertyInfo(boost::string_ref url,
                                                          Properties info) {
    return m_driver->getPropertyInfo(url, info);
  }
  // is this a regular SQL driver?
  int isSQL() {
    return m_driver->isSQL();
  }
  // Version of the driver itself
  int getMajorVersion() {
    return m_driver->getMajorVersion();
  }
  int getMinorVersion() {
    return m_driver->getMinorVersion();
  }
  // Version of the CxxDBC API implemented by the driver
  int getSupportedCxxDBCMajorVersion() {
    return m_driver->getSupportedCxxDBCMajorVersion();
  }
  int getSupportedCxxDBCMinorVersion() {
    return m_driver->getSupportedCxxDBCMinorVersion();
  }
};

bool operator==(Driver& a, Driver& b) {
  *(a.m_driver) == *(b.m_driver);
}

}  // namespace v1_0
}  // namespace cxxdbc

#endif  // INCLUDED_CXXDBC_1_0_DRIVER_H
