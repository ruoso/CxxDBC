#ifndef INCLUDED_CXXDBC_STATEMENT_H
#define INCLUDED_CXXDBC_STATEMENT_H

// third-party includes
#include <boost/utility/string_ref.hpp>

// standard includes
#include <memory>

namespace cxxdbc {

/// Defines the v-table for dynamic dispatch to a driver implementation of the statement concept.
class IStatement {
public:  // RAII
  virtual ~IStatement() = default;

public:  // methods
  virtual void close() = 0;

  virtual bool execute(::boost::string_ref query) = 0;

  virtual bool isClosed() const = 0;
};

/// A handle to a statement
class Statement {
private:  // variables
  ::std::unique_ptr<IStatement> m_statement;

public:  // RAII
  Statement() = delete;

  Statement(Statement const &) = delete;

  Statement(Statement &&) = default;

  Statement(::std::unique_ptr<IStatement> statement) : m_statement(::std::move(statement)) {}

  ~Statement() {}

public:  // methods
  void close() { m_statement->close(); }

  bool execute(::boost::string_ref query) { return m_statement->execute(query); }

  bool isClosed() const { return m_statement->isClosed(); }
};

}  // namespace cxxdbc

#endif  // INCLUDED_CXXDBC_STATEMENT_H
