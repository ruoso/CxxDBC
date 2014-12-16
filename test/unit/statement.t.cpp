// CxxDBC includes
#include <cxxdbc/statement.h>

// third party includes
#include <gtest/gtest.h>

namespace {

  class TestStatement : public ::cxxdbc::IStatement {
public:  // methods
  bool execute(::boost::string_ref query) { return query == "this query works"; }
  bool isClosed() const { return false; }
  void close() {}
};

}  // anonymous namespace

TEST(Statement, Close) {
  TestStatement* ptr = new TestStatement();
  ::std::unique_ptr<cxxdbc::IStatement> wrapper(ptr);
  ::cxxdbc::Statement statement(std::move(wrapper));
  ASSERT_FALSE(statement.isClosed());
  statement.close();
}

TEST(Statement, Execute) {
  TestStatement* ptr = new TestStatement();
  ::std::unique_ptr<cxxdbc::IStatement> wrapper(ptr);
  ::cxxdbc::Statement statement(std::move(wrapper));
  ASSERT_TRUE(statement.execute("this query works"));
  ASSERT_FALSE(statement.execute("this query doesn't work"));
}
