// CxxDBC includes
#include <cxxdbc/connection.h>

// third party includes
#include <gtest/gtest.h>

namespace {
using ::cxxdbc::Connection;

struct TestConnection {
  void clearWarnings() {}

  void close() {}

  void commit() {}

  bool isClosed() const { return false; }

  bool isReadOnly() const { return true; }

  void rollback() {}
};

::cxxdbc::Connection makeTestConnection() { return ::cxxdbc::Connection(TestConnection()); }

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
