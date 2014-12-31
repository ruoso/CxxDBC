// CxxDBC includes
#include <cxxdbc/1.0/statement.h>
#include <cxxdbc/1.0/concept/statement.h>

// third party includes
#include <gtest/gtest.h>

namespace {

class TestStatementInheritance : public ::cxxdbc::v1_0::IStatement {
public:  // methods
  bool execute(::boost::string_ref query) { return query == "this query works"; }
  bool isClosed() const { return false; }
  void close() {}

  static cxxdbc::v1_0::Statement makeStatement() {
    TestStatementInheritance* ptr = new TestStatementInheritance();
    ::std::unique_ptr<cxxdbc::v1_0::IStatement> wrapper(ptr);
    ::cxxdbc::v1_0::Statement statement(std::move(wrapper));
    return statement;
  }
};

class TestStatementWrapped {
public:
  bool execute(::boost::string_ref query) { return query == "this query works"; }
  bool isClosed() const { return false; }
  void close() {}
};

}  // anonymous namespace

TEST(Statement, Close) {
  ::cxxdbc::v1_0::Statement statement = TestStatementInheritance::makeStatement();
  ASSERT_FALSE(statement.isClosed());
  statement.close();
}

TEST(Statement, Execute) {
  ::cxxdbc::v1_0::Statement statement = TestStatementInheritance::makeStatement();
  ASSERT_TRUE(statement.execute("this query works"));
  ASSERT_FALSE(statement.execute("this query doesn't work"));
}

TEST(StatementWrapper, Close) {
  TestStatementWrapped realdriver;
  ::cxxdbc::v1_0::Statement statement = ::cxxdbc::v1_0::concept::makeStatement(realdriver);
  ASSERT_FALSE(statement.isClosed());
  statement.close();
}

TEST(StatementWrapper, Execute) {
  TestStatementWrapped realdriver;
  ::cxxdbc::v1_0::Statement statement = ::cxxdbc::v1_0::concept::makeStatement(realdriver);
  ASSERT_TRUE(statement.execute("this query works"));
  ASSERT_FALSE(statement.execute("this query doesn't work"));
}
