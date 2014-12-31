#ifndef INCLUDED_CXXDBC_1_0_CONNECTION_H
#define INCLUDED_CXXDBC_1_0_CONNECTION_H

// CxxDBC includes
#include <cxxdbc/1.0/support/make_unique.h>

// CxxDBC concept includes
#include <cxxdbc/1.0/concept/connection.h>

// standard includes
#include <memory>

namespace cxxdbc {
namespace v1_0 {

/// A handle to a database connection
class Connection final {
private:  // variables
  ::std::unique_ptr<concept::IConnection> m_connection;

public:  // RAII
  Connection() = delete;

  Connection(Connection const &) = delete;

  Connection(Connection &&) = default;

  template <typename Tconcept>
  explicit Connection(Tconcept &&concept)
      : m_connection(
            make_unique<concept::ConnectionWrapper<Tconcept>>(::std::forward<Tconcept>(concept))) {}

  ~Connection() {}

public:  // methods
  void clearWarnings() { m_connection->clearWarnings(); }

  void close() { m_connection->close(); }

  void commit() { m_connection->commit(); }

  bool isClosed() const { return m_connection->isClosed(); }

  bool isReadOnly() const { return m_connection->isReadOnly(); }

  void rollback() { m_connection->rollback(); }

public:  // operators
  Connection &operator=(Connection const &) = delete;

  Connection &operator=(Connection &&) = default;
};

}  // namespace v1_0
}  // namespace cxxdbc

#endif  // INCLUDED_CXXDBC_1_0_CONNECTION_H
