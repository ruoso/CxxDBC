#ifndef INCLUDED_CXXDBC_RESULT_SET_META_DATA_H
#define INCLUDED_CXXDBC_RESULT_SET_META_DATA_H

// CxxDBC includes
#include <cxxdbc/make_unique.h>
#include <cxxdbc/type.h>

// CxxDBC concept includes
#include <cxxdbc/concept/result_set_meta_data.h>

// third party includes
#include <boost/utility/string_ref.hpp>

// standard includes
#include <memory>

namespace cxxdbc {

// A handle to metadata about a set of query results
class ResultSetMetaData {
private:  // variables
  ::std::unique_ptr<concept::IResultSetMetaData> m_impl;

public:  // RAII
  ResultSetMetaData() = delete;

  ResultSetMetaData(ResultSetMetaData const &) = delete;

  ResultSetMetaData(ResultSetMetaData &&) = default;

  template <typename Tconcept>
  explicit ResultSetMetaData(Tconcept &&concept)
      : m_impl(make_unique<concept::ResultSetMetaDataWrapper<Tconcept>>(
            ::std::forward<Tconcept>(concept))) {}

  ~ResultSetMetaData() {}

public:  // methods
  size_t getColumnCount() const { return m_impl->getColumnCount(); }

  ::boost::string_ref getColumnName(size_t column) const { return m_impl->getColumnName(column); }

  Type getColumnType(size_t column) const { return m_impl->getColumnType(column); }

  bool isNullable(size_t column) const { return m_impl->isNullable(column); }
};

}  // namespace cxxdbc

#endif  // INCLUDED_CXXDBC_RESULT_SET_META_DATA_H
