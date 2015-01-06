// matching include
#include <cxxdbc/1.0/driver_manager.h>
#include <cxxdbc/1.0/exception.h>

// standard includes
#include <algorithm>

namespace cxxdbc {
namespace v1_0 {

::std::vector<Driver> DriverManager::s_registeredDrivers;

int DriverManager::s_loginTimeout = 0;

::std::ostream* DriverManager::s_logWriter = nullptr;

int DriverManager::deregisterDriver(Driver const& driver) {
  using ::std::begin;
  using ::std::end;
  using ::std::swap;

  auto const stop = end(s_registeredDrivers);
  auto found = ::std::find(begin(s_registeredDrivers), stop, driver);
  if (found != stop) {
    // We could use s_registeredDrivers.erase(found), but that has a worst case O(n) complexity.
    // We don't care to keep the order of elements stable, so swap with the last element and
    // them pop to do the same operation in O(1).
    swap(*found, s_registeredDrivers.back());
    s_registeredDrivers.pop_back();
    return 0;
  }
  return 1;
}

Connection DriverManager::getConnection(boost::string_ref url) {
  for(std::vector<Driver>::iterator it = s_registeredDrivers.begin();
      it != s_registeredDrivers.end();
      ++it) {
    if (it->acceptsURL(url)) {
      return it->connect(url, {});
    }
  }
  throw Exception("No driver accepts the given url");
}

Connection DriverManager::getConnection(boost::string_ref url, Properties properties) {
  (void)url;         // not used yet
  (void)properties;  // not used yet
  abort();
}

Connection DriverManager::getConnection(boost::string_ref url, boost::string_ref user,
                                        boost::string_ref password) {
  (void)url;       // not used yet
  (void)user;      // not used yet
  (void)password;  // not used yet
  abort();
}

Driver DriverManager::getDriver(boost::string_ref url) {
  (void)url;  // not used yet
  abort();
}

::std::vector<Driver> const& DriverManager::getDrivers() { return s_registeredDrivers; }

int DriverManager::getLoginTimeout() { return s_loginTimeout; }

::std::ostream* DriverManager::getLogWriter() { return s_logWriter; }

int DriverManager::registerDriver(Driver const& driver) {
  s_registeredDrivers.push_back(driver);
  return 0;
}

int DriverManager::setLoginTimeout(int timeout) {
  int old = s_loginTimeout;
  s_loginTimeout = timeout;
  return old;
}

::std::ostream* DriverManager::setLogWriter(::std::ostream* os) {
  auto old = s_logWriter;
  s_logWriter = os;
  return old;
}

}  // namespace v1_0
}  // namesapce cxxdbc
