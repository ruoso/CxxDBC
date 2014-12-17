// CxxDBC includes
#include <cxxdbc/statement.h>
#include <cxxdbc/concept/statement.h>

// third party includes
#include <gtest/gtest.h>

namespace {

class TestStatementInheritance : public ::cxxdbc::IStatement {
public:  // methods
  bool execute(::boost::string_ref query) { return query == "this query works"; }
  bool isClosed() const { return false; }
  void close() {}

  static cxxdbc::Statement makeStatement() {
    TestStatementInheritance* ptr = new TestStatementInheritance();
    ::std::unique_ptr<cxxdbc::IStatement> wrapper(ptr);
    ::cxxdbc::Statement statement(std::move(wrapper));
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
  ::cxxdbc::Statement statement = TestStatementInheritance::makeStatement();
  ASSERT_FALSE(statement.isClosed());
  statement.close();
}

TEST(Statement, Execute) {
  ::cxxdbc::Statement statement = TestStatementInheritance::makeStatement();
  ASSERT_TRUE(statement.execute("this query works"));
  ASSERT_FALSE(statement.execute("this query doesn't work"));
}

TEST(StatementWrapper, Close) {
  TestStatementWrapped realdriver;
  ::cxxdbc::Statement statement = ::cxxdbc::concept::makeStatement(realdriver);
  ASSERT_FALSE(statement.isClosed());
  statement.close();
}

TEST(StatementWrapper, Execute) {
  TestStatementWrapped realdriver;
  ::cxxdbc::Statement statement = ::cxxdbc::concept::makeStatement(realdriver);
  ASSERT_TRUE(statement.execute("this query works"));
  ASSERT_FALSE(statement.execute("this query doesn't work"));
}
