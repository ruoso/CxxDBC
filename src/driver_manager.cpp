#include <cxxdbc/1.0/driver_manager.h>

#include <vector>

namespace cxxdbc {
namespace v1_0 {

std::vector<Driver> DriverManager::registered_drivers;
int DriverManager::loginTimeout;
std::ostream* DriverManager::logWriter = NULL;

int DriverManager::registerDriver(const Driver driver) {
  registered_drivers.push_back(driver);
  return 0;
}

int DriverManager::deregisterDriver(const Driver driver) {
  int removed = 0;
  for (std::vector<Driver>::iterator it = registered_drivers.begin() ;
       it != registered_drivers.end(); ++it) {
    if (driver == *it) {
      registered_drivers.remove(it);
      removed = 1;
      break;
    }
  }
  if (removed)
    return 0;
  else
    return 1;
}

Connection DriverManager::getConnection(boost::string_ref url) {
  abort();
}

Connection DriverManager::getConnection(boost::string_ref url,
                         Properties properties) {
  abort();
}

Connection DriverManager::getConnection(boost::string_ref url,
                         boost::string_ref user,
                         boost::string_ref password) {
  abort();
}

Driver DriverManager::getDriver(boost::string_ref url) {
  abort();
}

std::vector<Driver> DriverManager::getDrivers() {
  return registered_drivers;
}

int DriverManager::getLoginTimeout() {
  return loginTimeout;
}

int DriverManager::setLoginTimeout(int timeout) {
  int old = loginTimeout;
  loginTimeout = timeout;
  return old;
}

std::ostream DriverManager::getLogWriter() {
  return logWriter;
}

void DriverManager::setLogWriter(std::ostream os) {
  std::ostream old = logWriter;
  logWriter = os;
  return old;
}

}  // namespace v1_0
}  // namesapce cxxdbc
