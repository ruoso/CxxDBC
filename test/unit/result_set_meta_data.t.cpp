// CxxDBC includes
#include <cxxdbc/result_set_meta_data.h>

// third party includes
#include <gtest/gtest.h>

namespace {

struct TestMetaData {
  size_t getColumnCount() const { return 77; }

  // TODO: Should use a ::std::string to return a copy of the data? Or is this reference good
  // enough?
  ::boost::string_ref getColumnName(size_t column) const {
    switch (column) {
      case 0: { return "zero"; }
      case 1: { return "one"; }
    }
    return "other";
  }

  ::cxxdbc::Type getColumnType(size_t column) const {
    using ::cxxdbc::Type;
    switch (column) {
      case 0: { return Type::array; }
      case 1: { return Type::integer; }
    }
    return Type::other;
  }
};

::cxxdbc::ResultSetMetaData getTestMetaData() {
  return ::cxxdbc::ResultSetMetaData(TestMetaData());
}

}  // anonymous namespace

TEST(ResultSetMetaData, Accessors) {
  ::cxxdbc::ResultSetMetaData metaData = getTestMetaData();

  ASSERT_EQ(77, metaData.getColumnCount());

  EXPECT_EQ("zero", metaData.getColumnName(0));
  EXPECT_EQ("one", metaData.getColumnName(1));
  EXPECT_EQ("other", metaData.getColumnName(99));

  EXPECT_EQ(::cxxdbc::Type::array, metaData.getColumnType(0));
  EXPECT_EQ(::cxxdbc::Type::integer, metaData.getColumnType(1));
  EXPECT_EQ(::cxxdbc::Type::other, metaData.getColumnType(123));
}
