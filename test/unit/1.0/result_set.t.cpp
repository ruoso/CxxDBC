// CxxDBC includes
#include <cxxdbc/1.0/result_set.h>

// third party includes
#include <gtest/gtest.h>

namespace {

class TestResultSet {
public:  // variables
  bool m_isClosed = false;

public:  // methods
  void close() { m_isClosed = true; }

  int getInt(size_t columnIndex) const { return static_cast<int>(columnIndex); }

  int getInt(::boost::string_ref columnName) const { return static_cast<int>(columnName.size()); }

  size_t findColumn(::boost::string_ref columnName) const { return columnName.size(); }

  bool isClosed() const { return m_isClosed; }
};

::cxxdbc::v1_0::ResultSet makeTestResultSet() { return ::cxxdbc::v1_0::ResultSet(TestResultSet()); }

}  // anonymous namespace

TEST(ResultSet, Close) {
  ::cxxdbc::v1_0::ResultSet resultSet = makeTestResultSet();
  ASSERT_FALSE(resultSet.isClosed());
  resultSet.close();
  ASSERT_TRUE(resultSet.isClosed());
}

TEST(ResultSet, Get) {
  ::cxxdbc::v1_0::ResultSet resultSet = makeTestResultSet();
  EXPECT_EQ(0, resultSet.getInt(0));
  EXPECT_EQ(999, resultSet.getInt(999));
  EXPECT_EQ(1, resultSet.getInt("a"));
  EXPECT_EQ(6, resultSet.getInt("foobar"));
  EXPECT_EQ(2, resultSet.findColumn("id"));
}
