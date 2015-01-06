// CxxDBC includes
#include <cxxdbc/1.0/driver.h>
#include <cxxdbc/1.0/driver_manager.h>
#include <cxxdbc/1.0/exception.h>

// test includes
#include <../test/nulldriver/null_driver.h>

// third party includes
#include <gtest/gtest.h>

TEST(DriverManager, DefaultLoginTimeout) {
  int r = cxxdbc::v1_0::DriverManager::getLoginTimeout();
  ASSERT_TRUE(r == 0);
}

TEST(DriverManager, RegisterDriver) {
  cxxdbc::v1_0::Driver d1 = cxxdbc::nulldriver::NullDriver::makeDriver();
  size_t i = cxxdbc::v1_0::DriverManager::getDrivers().size();
  cxxdbc::v1_0::DriverManager::registerDriver(d1);
  EXPECT_TRUE(cxxdbc::v1_0::DriverManager::getDrivers().size() == i + 1);
}

// todo: this is failing for now
TEST(DriverManager, DISABLED_deregisterDriver) {
  size_t i = cxxdbc::v1_0::DriverManager::getDrivers().size();
  cxxdbc::v1_0::Driver d1 = cxxdbc::nulldriver::NullDriver::makeDriver();
  cxxdbc::v1_0::Driver d2 = cxxdbc::nulldriver::NullDriver::makeDriver();
  cxxdbc::v1_0::DriverManager::registerDriver(d1);
  cxxdbc::v1_0::DriverManager::registerDriver(d2);
  EXPECT_TRUE(cxxdbc::v1_0::DriverManager::deregisterDriver(d2));
  EXPECT_TRUE(cxxdbc::v1_0::DriverManager::getDrivers().size() == i + 1);
  EXPECT_TRUE(cxxdbc::v1_0::DriverManager::deregisterDriver(d1));
  EXPECT_TRUE(cxxdbc::v1_0::DriverManager::getDrivers().size() == i);
}

TEST(DriverManager, connect) {
  cxxdbc::v1_0::Driver d1 = cxxdbc::nulldriver::NullDriver::makeDriver();
  cxxdbc::v1_0::DriverManager::registerDriver(d1);
  cxxdbc::v1_0::Connection c =
    cxxdbc::v1_0::DriverManager::getConnection("null:connection");
  EXPECT_TRUE(c.isReadOnly()); // null driver is always read only.
  EXPECT_THROW(cxxdbc::v1_0::DriverManager::getConnection("non-existant"),
               cxxdbc::v1_0::Exception);
}

