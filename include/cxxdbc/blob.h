#ifndef INCLUDED_CXXDBC_BLOB_H
#define INCLUDED_CXXDBC_BLOB_H

// standard includes
#include <cstddef>
#include <memory>

// CxxDBC includes
#include <cxxdbc/make_unique.h>

namespace cxxdbc {

class IBlobImpl {
public:  // RAII
  virtual ~IBlobImpl() = default;

public:  // methods
  virtual char *begin() = 0;

  virtual char const *begin() const = 0;

  virtual char *end() = 0;

  virtual char const *end() const = 0;

  virtual ptrdiff_t length() const = 0;
};

template <typename Timpl>
class BlobImpl : public IBlobImpl {
private:  // variables
  Timpl m_impl;

public:  // RAII
  BlobImpl() = default;

  BlobImpl(BlobImpl const &) = delete;

  BlobImpl(BlobImpl &&) = delete;

  explicit BlobImpl(Timpl &&impl) : m_impl(::std::forward<Timpl>(impl)) {}

  ~BlobImpl() = default;

public:  // methods
  char *begin() override final { return m_impl.begin(); }

  char const *begin() const override final { return m_impl.begin(); }

  char *end() override final { return m_impl.end(); }

  char const *end() const override final { return m_impl.end(); }

  ptrdiff_t length() const override final { return m_impl.length(); }

public:  // operators
  BlobImpl<Timpl> &operator=(BlobImpl<Timpl> const &) = delete;

  BlobImpl<Timpl> &operator=(BlobImpl<Timpl> &&) = delete;
};

class Blob {
public:  // types
  struct Iterator {
  private:  // variables
    char *m_ptr = nullptr;

  public:  // RAII
    Iterator() = default;

    Iterator(Iterator const &) = default;

    Iterator(Iterator &&) = default;

    explicit Iterator(char *ptr) : m_ptr(ptr) {}

    ~Iterator() = default;

  public:  // operators
    Iterator operator++(int) { return Iterator(m_ptr++); }

    Iterator &operator++() {
      ++m_ptr;
      return *this;
    }

    char &operator*() { return *m_ptr; }

    char const &operator*() const { return *m_ptr; }

    Iterator &operator=(Iterator const &) = default;

    Iterator &operator=(Iterator &&) = default;

    Iterator operator+(ptrdiff_t n) const { return Iterator(m_ptr + n); }

    ptrdiff_t operator-(Iterator const &rhs) const { return m_ptr - rhs.m_ptr; }

    bool operator==(Iterator const &rhs) const { return m_ptr == rhs.m_ptr; }

    bool operator!=(Iterator const &rhs) const { return m_ptr != rhs.m_ptr; }
  };

  struct ConstIterator {
  private:  // variables
    char const *m_ptr = nullptr;

  public:  // RAII
    ConstIterator() = default;

    ConstIterator(ConstIterator const &) = default;

    ConstIterator(ConstIterator &&) = default;

    explicit ConstIterator(char const *ptr) : m_ptr(ptr) {}

    ~ConstIterator() = default;

  public:  // operators
    ConstIterator operator++(int) { return ConstIterator(m_ptr++); }

    ConstIterator &operator++() {
      ++m_ptr;
      return *this;
    }

    char const &operator*() const { return *m_ptr; }

    ConstIterator &operator=(ConstIterator const &) = default;

    ConstIterator &operator=(ConstIterator &&) = default;

    ConstIterator operator+(ptrdiff_t n) const { return ConstIterator(m_ptr + n); }

    ptrdiff_t operator-(ConstIterator const &rhs) const { return m_ptr - rhs.m_ptr; }

    bool operator==(ConstIterator const &rhs) const { return m_ptr == rhs.m_ptr; }

    bool operator!=(ConstIterator const &rhs) const { return m_ptr != rhs.m_ptr; }
  };

private:  // variables
  ::std::unique_ptr<IBlobImpl> m_impl;

public:  // RAII
  Blob() = delete;

  Blob(Blob const &) = delete;

  Blob(Blob &&) = default;

  template <typename Timpl>
  explicit Blob(Timpl &&impl)
      : m_impl(make_unique<BlobImpl<Timpl>>(::std::forward<Timpl>(impl))) {}

  ~Blob() {}

public:  // methods
  ConstIterator cbegin() const { return ConstIterator(m_impl->begin()); }

  ConstIterator cend() const { return ConstIterator(m_impl->end()); }

  Iterator begin() { return Iterator(m_impl->begin()); }

  Iterator end() { return Iterator(m_impl->end()); }

  ConstIterator begin() const { return ConstIterator(m_impl->begin()); }

  ConstIterator end() const { return ConstIterator(m_impl->end()); }

  ptrdiff_t length() const { return m_impl->length(); }
};

}  // namespace cxxdbc

namespace std {
template <>
struct iterator_traits<::cxxdbc::Blob::Iterator> {
  typedef char value_type;
  typedef ptrdiff_t difference_type;
  typedef random_access_iterator_tag iterator_category;
  typedef char *pointer;
  typedef char &reference;
};

template <>
struct iterator_traits<::cxxdbc::Blob::ConstIterator> {
  typedef char const value_type;
  typedef ptrdiff_t difference_type;
  typedef random_access_iterator_tag iterator_category;
  typedef char const *pointer;
  typedef char const &reference;
};
}  // namespace std

#endif  // INCLUDED_CXXDBC_BLOB_H
