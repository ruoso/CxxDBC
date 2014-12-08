// CxxDBC includes
#include <cxxdbc/exception.h>

// third party includes
#include <gtest/gtest.h>

namespace {

void throwException(::boost::string_ref reason) { throw ::cxxdbc::Exception(reason); }

}  // anonymous namespace

TEST(Exception, CatchAsCxxDBCException) {
  try {
    throwException("test");
    FAIL() << "Should have thrown an ::cxxdbc::Exception. This line should be unreachable.";
  }
  catch (::cxxdbc::Exception& e) {
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
    FAIL() << "Should have thrown an ::cxxdbc::Exception. This line should be unreachable.";
  }
  catch (::std::exception& e) {
    EXPECT_STREQ("test", e.what());
  }
}
