#ifndef INCLUDED_CXXDBC_STATEMENT_H
#define INCLUDED_CXXDBC_STATEMENT_H

// CxxDBC includes
#include <cxxdbc/support/make_unique.h>

// CxxDBC concept includes
#include <cxxdbc/concept/statement.h>

// third-party includes
#include <boost/utility/string_ref.hpp>

// standard includes
#include <memory>

namespace cxxdbc {

/// A handle to a statement
class Statement {
private:  // variables
  ::std::unique_ptr<concept::IStatement> m_statement;

public:  // RAII
  Statement() = delete;

  Statement(Statement const &) = delete;

  Statement(Statement &&) = default;

  template <typename Tconcept>
  explicit Statement(Tconcept &&concept)
      : m_statement(
            make_unique<concept::StatementWrapper<Tconcept>>(::std::forward<Tconcept>(concept))) {}

  ~Statement() {}

public:  // methods
  void close() { m_statement->close(); }

  bool execute(::boost::string_ref query) { return m_statement->execute(query); }

  bool isClosed() const { return m_statement->isClosed(); }
};

}  // namespace cxxdbc

#endif  // INCLUDED_CXXDBC_STATEMENT_H
