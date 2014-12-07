#ifndef INCLUDED_CXXDBC_RESULT_SET_META_DATA_H
#define INCLUDED_CXXDBC_RESULT_SET_META_DATA_H

// CxxDBC includes
#include <cxxdbc/make_unique.h>

// third party includes
#include <boost/utility/string_ref.hpp>

// standard includes
#include <memory>

namespace cxxdbc {

class IResultSetMetaDataImpl {
public:  // RAII
  virtual ~IResultSetMetaDataImpl() = default;

public:  // methods
  virtual size_t getColumnCount() const = 0;

  virtual ::boost::string_ref getColumnName(size_t column) const = 0;
};

template <typename Timpl>
class ResultSetMetaDataImpl : public IResultSetMetaDataImpl {
private:  // variables
  Timpl m_impl;

public:  // RAII
  ResultSetMetaDataImpl() = default;

  ResultSetMetaDataImpl(ResultSetMetaDataImpl const &) = delete;

  ResultSetMetaDataImpl(ResultSetMetaDataImpl &&) = delete;

  explicit ResultSetMetaDataImpl(Timpl &&impl) : m_impl(::std::forward<Timpl>(impl)) {}

  ~ResultSetMetaDataImpl() = default;

public:  // methods
  size_t getColumnCount() const override final { return m_impl.getColumnCount(); }

  ::boost::string_ref getColumnName(size_t column) const override final {
    return m_impl.getColumnName(column);
  }

public:  // operators
  ResultSetMetaDataImpl<Timpl> &operator=(ResultSetMetaDataImpl<Timpl> const &) = delete;

  ResultSetMetaDataImpl<Timpl> &operator=(ResultSetMetaDataImpl<Timpl> &&) = delete;
};

class ResultSetMetaData {
private:  // variables
  ::std::unique_ptr<IResultSetMetaDataImpl> m_impl;

public:  // RAII
  ResultSetMetaData() = delete;

  ResultSetMetaData(ResultSetMetaData const &) = delete;

  ResultSetMetaData(ResultSetMetaData &&) = default;

  template <typename Timpl>
  explicit ResultSetMetaData(Timpl &&impl)
      : m_impl(make_unique<ResultSetMetaDataImpl<Timpl>>(::std::forward<Timpl>(impl))) {}

  ~ResultSetMetaData() {}

public:  // methods
  size_t getColumnCount() const { return m_impl->getColumnCount(); }

  ::boost::string_ref getColumnName(size_t column) const { return m_impl->getColumnName(column); }
};

}  // namespace cxxdbc

#endif  // INCLUDED_CXXDBC_RESULT_SET_META_DATA_H
