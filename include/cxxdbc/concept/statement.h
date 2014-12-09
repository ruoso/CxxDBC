#ifndef INCLUDED_CXXDBC_CONCEPT_STATEMENT_H
#define INCLUDED_CXXDBC_CONCEPT_STATEMENT_H

// third-party includes
#include <boost/utility/string_ref.hpp>

namespace cxxdbc {
namespace concept {

/// Defines the v-table for dynamic dispatch to a driver implementation of the statement concept.
class IStatement {
public:  // RAII
  virtual ~IStatement() = default;

public:  // methods
  virtual void close() = 0;

  virtual bool execute(::boost::string_ref query) = 0;

  virtual bool isClosed() const = 0;
};

/// Wraps a driver implementation of the statement concept (Tconcept) and provides lifecycle
/// management.
///
/// \todo Define the statement concept
template <typename Tconcept>
class StatementWrapper : public IStatement {
private:  // variables
  Tconcept m_concept;

public:  // RAII
  StatementWrapper() = default;

  StatementWrapper(StatementWrapper const &) = delete;

  StatementWrapper(StatementWrapper &&) = delete;

  explicit StatementWrapper(Tconcept &&m_concept)
      : m_concept(::std::forward<Tconcept>(m_concept)) {}

  ~StatementWrapper() = default;

public:  // methods
  void close() override final { m_concept.close(); }

  bool execute(::boost::string_ref query) override final { return m_concept.execute(query); }

  bool isClosed() const override final { return m_concept.isClosed(); }

public:  // operators
  StatementWrapper<Tconcept> &operator=(StatementWrapper<Tconcept> const &) = delete;

  StatementWrapper<Tconcept> &operator=(StatementWrapper<Tconcept> &&) = delete;
};

}  // namespace concept
}  // namespace cxxdbc

#endif  // INCLUDED_CXXDBC_CONCEPT_STATEMENT_H
