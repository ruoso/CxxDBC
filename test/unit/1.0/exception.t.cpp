// CxxDBC includes
#include <cxxdbc/1.0/exception.h>

// third party includes
#include <gtest/gtest.h>

namespace {

void throwException(::boost::string_ref reason) { throw ::cxxdbc::v1_0::Exception(reason); }

}  // anonymous namespace

TEST(Exception, CatchAsCxxDBCException) {
  try {
    throwException("test");
    FAIL() << "Should have thrown an ::cxxdbc::v1_0::Exception. This line should be unreachable.";
  }
  catch (::cxxdbc::v1_0::Exception& e) {
    EXPECT_STREQ("test", e.what());
    EXPECT_EQ("test", e.reason());
    EXPECT_TRUE(e.sqlState().empty());
    EXPECT_EQ(0, e.vendorCode());
  }
}

// Should be able to catch a CxxDBC exception as a std::exception
TEST(Exception, CatchAsStdException) {
  try {
    throwException("test");
    FAIL() << "Should have thrown an ::cxxdbc::v1_0::Exception. This line should be unreachable.";
  }
  catch (::std::exception& e) {
    EXPECT_STREQ("test", e.what());
  }
}
