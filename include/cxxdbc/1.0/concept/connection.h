#ifndef INCLUDED_CXXDBC_1_0_CONCEPT_CONNECTION_H
#define INCLUDED_CXXDBC_1_0_CONCEPT_CONNECTION_H

namespace cxxdbc {
namespace v1_0 {
namespace concept {

/// Defines the v-table for dynamic dispatch to a driver implementation of the connection concept.
class IConnection {
public:  // RAII
  virtual ~IConnection() = default;

public:  // methods
  virtual void clearWarnings() = 0;

  virtual void close() = 0;

  virtual void commit() = 0;

  virtual bool isClosed() const = 0;

  virtual bool isReadOnly() const = 0;

  virtual void rollback() = 0;
};

/// Wraps a driver implementation of the connection concept (Tconcept) and provides lifecycle
/// management.
///
/// \todo Define the connection concept
template <typename Tconcept>
class ConnectionWrapper : public IConnection {
private:  // variables
  Tconcept m_concept;

public:  // RAII
  ConnectionWrapper() = default;

  ConnectionWrapper(ConnectionWrapper const &) = delete;

  ConnectionWrapper(ConnectionWrapper &&) = delete;

  explicit ConnectionWrapper(Tconcept &&concept) : m_concept(::std::forward<Tconcept>(concept)) {}

  ~ConnectionWrapper() = default;

public:  // methods
  void clearWarnings() override final { m_concept.clearWarnings(); }

  void close() override final { m_concept.close(); }

  void commit() override final { m_concept.commit(); }

  bool isClosed() const override final { return m_concept.isClosed(); }

  bool isReadOnly() const override final { return m_concept.isReadOnly(); }

  void rollback() override final { m_concept.rollback(); }

public:  // operators
  ConnectionWrapper<Tconcept> &operator=(ConnectionWrapper<Tconcept> const &) = delete;

  ConnectionWrapper<Tconcept> &operator=(ConnectionWrapper<Tconcept> &&) = delete;
};

}  // namespace concept
}  // namespace v1_0
}  // namespace cxxdbc

#endif  // INCLUDED_CXXDBC_1_0_CONCEPT_CONNECTION_H
