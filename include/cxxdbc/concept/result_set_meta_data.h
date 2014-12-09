#ifndef INCLUDED_CXXDBC_CONCEPT_RESULT_SET_META_DATA_H
#define INCLUDED_CXXDBC_CONCEPT_RESULT_SET_META_DATA_H

// third party includes
#include <boost/utility/string_ref.hpp>

namespace cxxdbc {
namespace concept {

/// Defines the v-table for dynamic dispatch to a driver implementation of the result set meta data
/// concept.
class IResultSetMetaData {
public:  // RAII
  virtual ~IResultSetMetaData() = default;

public:  // methods
  virtual size_t getColumnCount() const = 0;

  virtual ::boost::string_ref getColumnName(size_t column) const = 0;

  virtual Type getColumnType(size_t column) const = 0;

  virtual bool isNullable(size_t column) const = 0;
};

/// Wraps a driver implementation of the result set meta data concept (Tconcept) and provides
/// lifecycle management.
///
/// \todo Define the result set concept
template <typename Tconcept>
class ResultSetMetaDataWrapper : public IResultSetMetaData {
private:  // variables
  Tconcept m_concept;

public:  // RAII
  ResultSetMetaDataWrapper() = default;

  ResultSetMetaDataWrapper(ResultSetMetaDataWrapper const &) = delete;

  ResultSetMetaDataWrapper(ResultSetMetaDataWrapper &&) = delete;

  explicit ResultSetMetaDataWrapper(Tconcept &&concept)
      : m_concept(::std::forward<Tconcept>(concept)) {}

  ~ResultSetMetaDataWrapper() = default;

public:  // methods
  size_t getColumnCount() const override final { return m_concept.getColumnCount(); }

  ::boost::string_ref getColumnName(size_t column) const override final {
    return m_concept.getColumnName(column);
  }

  Type getColumnType(size_t column) const override final { return m_concept.getColumnType(column); }

  bool isNullable(size_t column) const override final { return m_concept.isNullable(column); }

public:  // operators
  ResultSetMetaDataWrapper<Tconcept> &operator=(ResultSetMetaDataWrapper<Tconcept> const &) =
      delete;

  ResultSetMetaDataWrapper<Tconcept> &operator=(ResultSetMetaDataWrapper<Tconcept> &&) = delete;
};

}  // namespace concept
}  // namespace cxxdbc

#endif  // INCLUDED_CXXDBC_CONCEPT_RESULT_SET_META_DATA_H
