#ifndef INCLUDED_CXXDBC_RESULT_SET_H
#define INCLUDED_CXXDBC_RESULT_SET_H

// CxxDBC includes
#include <cxxdbc/make_unique.h>

// third party includes
#include <boost/utility/string_ref.hpp>

// standard includes
#include <memory>

namespace cxxdbc {

class IResultSetImpl {
public:  // RAII
  virtual ~IResultSetImpl() = default;

public:  // methods
  virtual void close() = 0;

  virtual int getInt(size_t columnIndex) const = 0;

  virtual int getInt(::boost::string_ref columnName) const = 0;

  virtual size_t findColumn(::boost::string_ref columnName) const = 0;

  virtual bool isClosed() const = 0;
};

template <typename Timpl>
class ResultSetImpl : public IResultSetImpl {
private:  // variables
  Timpl m_impl;

public:  // RAII
  ResultSetImpl() = default;

  ResultSetImpl(ResultSetImpl const &) = delete;

  ResultSetImpl(ResultSetImpl &&) = delete;

  explicit ResultSetImpl(Timpl &&impl) : m_impl(::std::forward<Timpl>(impl)) {}

  ~ResultSetImpl() = default;

public:  // methods
  void close() override final { m_impl.close(); }

  int getInt(size_t columnIndex) const override final { return m_impl.getInt(columnIndex); }

  int getInt(::boost::string_ref columnName) const override final {
    return m_impl.getInt(columnName);
  }

  size_t findColumn(::boost::string_ref columnName) const override final {
    return m_impl.findColumn(columnName);
  }

  bool isClosed() const override final { return m_impl.isClosed(); }

public:  // operators
  ResultSetImpl<Timpl> &operator=(ResultSetImpl<Timpl> const &) = delete;

  ResultSetImpl<Timpl> &operator=(ResultSetImpl<Timpl> &&) = delete;
};

class ResultSet {
private:  // variables
  ::std::unique_ptr<IResultSetImpl> m_impl;

public:  // RAII
  ResultSet() = delete;

  ResultSet(ResultSet const &) = delete;

  ResultSet(ResultSet &&) = default;

  template <typename Timpl>
  explicit ResultSet(Timpl &&impl)
      : m_impl(make_unique<ResultSetImpl<Timpl>>(::std::forward<Timpl>(impl))) {}

  ~ResultSet() {}

public:  // methods
  void close() { m_impl->close(); }

  int getInt(size_t columnIndex) const { return m_impl->getInt(columnIndex); }

  int getInt(::boost::string_ref columnName) const { return m_impl->getInt(columnName); }

  size_t findColumn(::boost::string_ref columnName) const { return m_impl->findColumn(columnName); }

  bool isClosed() const { return m_impl->isClosed(); }
};

}  // namespace cxxdbc

#endif  // INCLUDED_CXXDBC_RESULT_SET_H
