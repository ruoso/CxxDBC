// CxxDBC includes
#include <cxxdbc/1.0/driver.h>

// third party includes
#include <gtest/gtest.h>

namespace {

using ::cxxdbc::v1_0::Connection;
using ::cxxdbc::v1_0::DriverPropertyInfo;
using ::cxxdbc::v1_0::Properties;

struct TestConnection {
  void clearWarnings() {}

  void close() {}

  void commit() {}

  bool isClosed() const { return false; }

  bool isReadOnly() const { return true; }

  void rollback() {}
};

::cxxdbc::v1_0::Connection makeTestConnection() {
  return ::cxxdbc::v1_0::Connection(TestConnection());
}

class TestDriverImpl : public ::cxxdbc::v1_0::IDriver {
public:  // methods
  bool acceptsURL(boost::string_ref url) const {
    (void)url; // unused
    return 1;
  }

  Connection connect(boost::string_ref url, Properties info) {
    (void)url; // unused
    (void)info; // unused
    return makeTestConnection();
  }

  int getMajorVersion() const {
    return 1;
  }

  int getMinorVersion() const {
    return 0;
  }

  std::vector<DriverPropertyInfo> getPropertyInfo(boost::string_ref url,
                                                  Properties info) const {
    (void)url; // unused
    (void)info; // unused;
    std::vector<DriverPropertyInfo> ret = {};
    return ret;
  }

  int getSupportedCxxDBCMajorVersion() const {
    return 1;
  }

  int getSupportedCxxDBCMinorVersion() const {
    return 0;
  }

  bool isEqual(IDriver const &driver) const {
    (void)driver; // unused
    return 0;
  }

  bool isSQL() const {
    return 1;
  }

  static cxxdbc::v1_0::Driver makeTestDriver() {
    TestDriverImpl* ptr = new TestDriverImpl();
    ::std::shared_ptr<cxxdbc::v1_0::IDriver> wrapper(ptr);
    ::cxxdbc::v1_0::Driver driver(std::move(wrapper));
    return driver;
  }

};

}  // anonymous namespace

TEST(Driver, isSQL) {
  ::cxxdbc::v1_0::Driver driver = TestDriverImpl::makeTestDriver();
  ASSERT_TRUE(driver.isSQL());
}

