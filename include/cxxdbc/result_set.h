#ifndef INCLUDED_CXXDBC_RESULT_SET_H
#define INCLUDED_CXXDBC_RESULT_SET_H

// CxxDBC includes
#include <cxxdbc/support/make_unique.h>

// CxxDBC concept includes
#include <cxxdbc/concept/result_set.h>

// third party includes
#include <boost/utility/string_ref.hpp>

// standard includes
#include <memory>

namespace cxxdbc {

// A handle to a set of query results
class ResultSet {
private:  // variables
  ::std::unique_ptr<concept::IResultSet> m_resultSet;

public:  // RAII
  ResultSet() = delete;

  ResultSet(ResultSet const &) = delete;

  ResultSet(ResultSet &&) = default;

  template <typename Tconcept>
  explicit ResultSet(Tconcept &&concept)
      : m_resultSet(
            make_unique<concept::ResultSetWrapper<Tconcept>>(::std::forward<Tconcept>(concept))) {}

  ~ResultSet() {}

public:  // methods
  void close() { m_resultSet->close(); }

  int getInt(size_t columnIndex) const { return m_resultSet->getInt(columnIndex); }

  int getInt(::boost::string_ref columnName) const { return m_resultSet->getInt(columnName); }

  size_t findColumn(::boost::string_ref columnName) const {
    return m_resultSet->findColumn(columnName);
  }

  bool isClosed() const { return m_resultSet->isClosed(); }
};

}  // namespace cxxdbc

#endif  // INCLUDED_CXXDBC_RESULT_SET_H
