#ifndef INCLUDED_CXXDBC_1_0_DRIVER_H
#define INCLUDED_CXXDBC_1_0_DRIVER_H

// cxxdbc includes
#include <cxxdbc/1.0/driver_property_info.h>
#include <cxxdbc/1.0/properties.h>
#include <cxxdbc/1.0/connection.h>

// third-party includes
#include <boost/utility/string_ref.hpp>

// standard includes
#include <memory>

namespace cxxdbc {
namespace v1_0 {

/// Defines the v-table for dynamic dispatch to a driver implementation of the driver concept.
class IDriver {
public:  // RAII
  virtual ~IDriver() = default;

public:  // methods
  virtual bool acceptsURL(boost::string_ref url) const = 0;

  virtual Connection connect(boost::string_ref url, Properties info) = 0;

  /// Version of the driver itself
  virtual int getMajorVersion() const = 0;

  virtual int getMinorVersion() const = 0;

  virtual std::vector<DriverPropertyInfo> getPropertyInfo(boost::string_ref url,
                                                          Properties info) const = 0;

  /// Version of the CxxDBC API implemented by the driver
  virtual int getSupportedCxxDBCMajorVersion() const = 0;

  virtual int getSupportedCxxDBCMinorVersion() const = 0;

  /// @todo There could be a simpler way of doing this. Just compare names and driver version
  /// numbers?
  virtual bool isEqual(IDriver const &driver) const = 0;

  /// is this a regular SQL driver?
  virtual bool isSQL() const = 0;
};

/// A handle to a driver
class Driver {
private:  // variables
  /// a driver handle can actually be held by several people
  /// at once. So we use shared_ptr instead of unique_ptr.
  ::std::shared_ptr<IDriver> m_driver;

public:  // RAII
  Driver() = default;

  Driver(const Driver &) = default;

  Driver(Driver &&) = default;

  explicit Driver(::std::shared_ptr<IDriver> &&driver) : m_driver(driver) {}

  ~Driver() {}

public:  // methods
  bool acceptsURL(boost::string_ref url) const { return m_driver->acceptsURL(url); }

  inline Connection connect(boost::string_ref url, Properties info) {
    return m_driver->connect(url, info);
  }

  inline ::std::vector<DriverPropertyInfo> getPropertyInfo(boost::string_ref url,
                                                           Properties info) const {
    return m_driver->getPropertyInfo(url, info);
  }

  /// Version of the driver itself
  inline int getMajorVersion() const { return m_driver->getMajorVersion(); }

  inline int getMinorVersion() const { return m_driver->getMinorVersion(); }

  /// Version of the CxxDBC API implemented by the driver
  inline int getSupportedCxxDBCMajorVersion() const {
    return m_driver->getSupportedCxxDBCMajorVersion();
  }

  inline int getSupportedCxxDBCMinorVersion() const {
    return m_driver->getSupportedCxxDBCMinorVersion();
  }

  /// is this a regular SQL driver?
  inline bool isSQL() const { return m_driver->isSQL(); }

  void swap(Driver &driver) {
    using ::std::swap;
    swap(m_driver, driver.m_driver);
  }

public:  // operators
  Driver &operator=(Driver &&driver) {
    this->swap(driver);
    return *this;
  }

  friend bool operator==(Driver const &a, Driver const &b) {
    return a.m_driver->isEqual(*b.m_driver);
  }
};

}  // namespace v1_0
}  // namespace cxxdbc

#endif  // INCLUDED_CXXDBC_1_0_DRIVER_H
