#ifndef INCLUDED_CXXDBC_1_0_CONCEPT_STATEMENT_H
#define INCLUDED_CXXDBC_1_0_CONCEPT_STATEMENT_H

// CxxDBC includes
#include <cxxdbc/1.0/support/make_unique.h>
#include <cxxdbc/1.0/statement.h>

// third-party includes
#include <boost/utility/string_ref.hpp>

namespace cxxdbc {
namespace v1_0 {
namespace concept {

/// Wraps a driver implementation of the statement concept (Tconcept) and provides lifecycle
/// management.
///
/// \todo Define the statement concept
template <typename Tconcept>
class StatementWrapper : public IStatement {
private:  // variables
  Tconcept &m_concept;

public:  // RAII
  StatementWrapper() = default;

  StatementWrapper(StatementWrapper const &) = delete;

  StatementWrapper(StatementWrapper &&) = delete;

  explicit StatementWrapper(Tconcept &&concept) : m_concept(::std::forward<Tconcept>(concept)) {}

  ~StatementWrapper() = default;

public:  // methods
  void close() override final { m_concept.close(); }

  bool execute(::boost::string_ref query) override final { return m_concept.execute(query); }

  bool isClosed() const override final { return m_concept.isClosed(); }

public:  // operators
  StatementWrapper<Tconcept> &operator=(StatementWrapper<Tconcept> const &) = delete;

  StatementWrapper<Tconcept> &operator=(StatementWrapper<Tconcept> &&) = delete;
};

template <typename Tconcept>
static Statement makeStatement(Tconcept &&concept) {
  // ...but use our homebrew make_unique until the standard one is available
  return Statement(make_unique<StatementWrapper<Tconcept>>(::std::forward<Tconcept>(concept)));
}

}  // namespace concept
}  // namespace v1_0
}  // namespace cxxdbc

#endif  // INCLUDED_CXXDBC_1_0_CONCEPT_STATEMENT_H
