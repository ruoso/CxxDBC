#ifndef INCLUDED_CXXDBC_1_0_DRIVER_MANAGER_H
#define INCLUDED_CXXDBC_1_0_DRIVER_MANAGER_H

// cxxdbc includes
#include <cxxdbc/1.0/properties.h>
#include <cxxdbc/1.0/driver.h>
#include <cxxdbc/1.0/connection.h>

// third-party includes
#include <boost/utility/string_ref.hpp>

// standard headers
#include <ostream>
#include <vector>

namespace cxxdbc {
namespace v1_0 {

/// @todo Use ::std::error_condition instead of int for error codes
/// @todo Use ::std::chrono::duration instead of int for timeouts
/// @todo Consider removing notions of loggers since there is not a standard C++ logger.
class DriverManager {
private:  // class variables
  static int s_loginTimeout;

  /// May be nullptr
  static std::ostream* s_logWriter;

  static std::vector<Driver> s_registeredDrivers;

public:  // class methods
  static int deregisterDriver(Driver const& driver);

  static Connection getConnection(boost::string_ref url);

  static Connection getConnection(boost::string_ref url, Properties properties);

  static Connection getConnection(boost::string_ref url, boost::string_ref user,
                                  boost::string_ref password);

  static Driver getDriver(boost::string_ref url);

  /// @todo Should getDrivers() return a copy of the Driver vector?
  static ::std::vector<Driver> const& getDrivers();

  static int getLoginTimeout();

  static ::std::ostream* getLogWriter();

  static int registerDriver(Driver const& driver);

  static int setLoginTimeout(int newtimeout);

  static ::std::ostream* setLogWriter(::std::ostream* os);
};

}  // namespace v1_0
}  // namespace cxxdbc

#endif  // INCLUDED_CXXDBC_1_0_DRIVER_MANAGER_H
