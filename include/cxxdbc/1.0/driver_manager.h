#ifndef INCLUDED_CXXDBC_1_0_DRIVER_MANAGER_H
#define INCLUDED_CXXDBC_1_0_DRIVER_MANAGER_H

// third-party includes
#include <boost/utility/string_ref.hpp>

// cxxdbc includes
#include <cxxdbc/1.0/properties.h>
#include <cxxdbc/1.0/driver.h>
#include <cxxdbc/1.0/connection.h>

// standard headers
#include <ostream>
#include <vector>

namespace cxxdbc {
namespace v1_0 {

class DriverManager {
public:
  static int registerDriver(Driver& driver);
  static int deregisterDriver(Driver& driver);
  static Connection getConnection(boost::string_ref url);
  static Connection getConnection(boost::string_ref url,
                                  Properties properties);
  static Connection getConnection(boost::string_ref url,
                                  boost::string_ref user,
                                  boost::string_ref password);
  static Driver getDriver(boost::string_ref url);
  static std::vector<Driver> getDrivers();
  static int getLoginTimeout();
  static int setLoginTimeout();
  static std::ostream getLogWriter();
  static void setLogWriter(std::ostream os);
};

}  // namespace v1_0
}  // namespace cxxdbc

#endif  // INCLUDED_CXXDBC_1_0_DRIVER_MANAGER_H
