// CxxDBC includes
#include <cxxdbc/1.0/connection.h>

// third party includes
#include <gtest/gtest.h>

namespace {
using ::cxxdbc::v1_0::Connection;

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

}  // anonymous namespace

TEST(Connection, AccessorsAndMutators) {
  Connection connection = makeTestConnection();
  EXPECT_FALSE(connection.isClosed());
  EXPECT_TRUE(connection.isReadOnly());
  connection.clearWarnings();
  connection.commit();
  connection.close();
  connection.rollback();
}
