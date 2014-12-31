#ifndef INCLUDED_CXXDBC_1_0_CONCEPT_RESULT_SET_H
#define INCLUDED_CXXDBC_1_0_CONCEPT_RESULT_SET_H

// third party includes
#include <boost/utility/string_ref.hpp>

namespace cxxdbc {
namespace v1_0 {
namespace concept {

/// Defines the v-table for dynamic dispatch to a driver implementation of the result set concept.
class IResultSet {
public:  // RAII
  virtual ~IResultSet() = default;

public:  // methods
  virtual void close() = 0;

  virtual int getInt(size_t columnIndex) const = 0;

  virtual int getInt(::boost::string_ref columnName) const = 0;

  virtual size_t findColumn(::boost::string_ref columnName) const = 0;

  virtual bool isClosed() const = 0;
};

/// Wraps a driver implementation of the result set concept (Tconcept) and provides lifecycle
/// management.
///
/// \todo Define the result set concept
template <typename Tconcept>
class ResultSetWrapper : public IResultSet {
private:  // variables
  Tconcept m_concept;

public:  // RAII
  ResultSetWrapper() = default;

  ResultSetWrapper(ResultSetWrapper const &) = delete;

  ResultSetWrapper(ResultSetWrapper &&) = delete;

  explicit ResultSetWrapper(Tconcept &&concept) : m_concept(::std::forward<Tconcept>(concept)) {}

  ~ResultSetWrapper() = default;

public:  // methods
  void close() override final { m_concept.close(); }

  int getInt(size_t columnIndex) const override final { return m_concept.getInt(columnIndex); }

  int getInt(::boost::string_ref columnName) const override final {
    return m_concept.getInt(columnName);
  }

  size_t findColumn(::boost::string_ref columnName) const override final {
    return m_concept.findColumn(columnName);
  }

  bool isClosed() const override final { return m_concept.isClosed(); }

public:  // operators
  ResultSetWrapper<Tconcept> &operator=(ResultSetWrapper<Tconcept> const &) = delete;

  ResultSetWrapper<Tconcept> &operator=(ResultSetWrapper<Tconcept> &&) = delete;
};

}  // namespace concept
}  // namespace v1_0
}  // namespace cxxdbc

#endif  // INCLUDED_CXXDBC_1_0_CONCEPT_RESULT_SET_H
