// CxxDBC includes
#include <cxxdbc/statement.h>

// third party includes
#include <gtest/gtest.h>

namespace {

class TestStatement {
public:  // methods
  bool execute(::boost::string_ref query) { return query == "this query works"; }
  bool isClosed() const { return false; }
  void close() {}
};

::cxxdbc::Statement makeTestStatement() { return ::cxxdbc::Statement(TestStatement()); }

}  // anonymous namespace

TEST(Statement, Close) {
  ::cxxdbc::Statement statement = makeTestStatement();
  ASSERT_FALSE(statement.isClosed());
  statement.close();
}

TEST(Statement, Execute) {
  ::cxxdbc::Statement statement = makeTestStatement();
  ASSERT_TRUE(statement.execute("this query works"));
  ASSERT_FALSE(statement.execute("this query doesn't work"));
}
