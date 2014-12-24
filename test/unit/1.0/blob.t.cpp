// CxxDBC includes
#include <cxxdbc/1.0/blob.h>

// third party includes
#include <gtest/gtest.h>

// standard includes
#include <algorithm>
#include <iterator>

namespace {

class TestBlob {
private:  // variables
  ::std::vector<char> m_bytes;

public:  // RAII
  TestBlob() {}

  TestBlob(TestBlob const &) = delete;

  TestBlob(TestBlob &&) = default;

  explicit TestBlob(ptrdiff_t n) : m_bytes(n) {}

  ~TestBlob() {}

public:  // methods
  char *begin() { return m_bytes.data(); }

  char const *begin() const { return m_bytes.data(); }

  char *end() { return m_bytes.data() + m_bytes.size(); }

  char const *end() const { return m_bytes.data() + m_bytes.size(); }

  ptrdiff_t length() const { return static_cast<ptrdiff_t>(m_bytes.size()); }

public:  // operators
  TestBlob &operator=(TestBlob const &) = delete;
  TestBlob &operator=(TestBlob &&) = default;
};

::cxxdbc::v1_0::Blob makeTestBlob() { return ::cxxdbc::v1_0::Blob(TestBlob()); }

::cxxdbc::v1_0::Blob makeTestBlob(ptrdiff_t n) { return ::cxxdbc::v1_0::Blob(TestBlob(n)); }

}  // anonymous namespace

TEST(Blob, AccessorsAndMutators) {
  using ::std::begin;
  using ::std::distance;
  using ::std::end;
  using ::std::equal;
  using ::std::generate;

  {
    ::cxxdbc::v1_0::Blob blob = makeTestBlob();
    ASSERT_EQ(0, blob.length());
    ASSERT_EQ(0, distance(begin(blob), end(blob)));
    ASSERT_EQ(0, distance(blob.cbegin(), blob.cend()));
  }

  {
    ::cxxdbc::v1_0::Blob blob = makeTestBlob(26);
    ASSERT_EQ(26, blob.length());
    ASSERT_EQ(26, distance(begin(blob), end(blob)));
    ASSERT_EQ(26, distance(blob.cbegin(), blob.cend()));

    char n = 'a';
    generate(begin(blob), end(blob), [&n] { return n++; });

    static char const letters[] = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_TRUE(equal(begin(blob), end(blob), begin(letters)));
  }
}
