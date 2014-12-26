// CxxDBC includes
#include <cxxdbc/1.0/driver_manager.h>

// third party includes
#include <gtest/gtest.h>

TEST(DriverManager, DefaultLoginTimeout) {
  int r = cxxdbc::v1_0::DriverManager::getLoginTimeout();
  ASSERT_TRUE(r == 0);
}
