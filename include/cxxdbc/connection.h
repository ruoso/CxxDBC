#ifndef INCLUDED_CXXDBC_CONNECTION_H
#define INCLUDED_CXXDBC_CONNECTION_H

// standard includes
#include <memory>

// CxxDBC includes
#include <cxxdbc/make_unique.h>

namespace cxxdbc {

class IConnectionImpl {
public:  // RAII
  virtual ~IConnectionImpl() = default;

public:  // methods
  virtual void clearWarnings() = 0;

  virtual void close() = 0;

  virtual void commit() = 0;

  virtual bool isClosed() const = 0;

  virtual bool isReadOnly() const = 0;

  virtual void rollback() = 0;
};

template <typename Timpl>
class ConnectionImpl : public IConnectionImpl {
private:  // variables
  Timpl m_impl;

public:  // RAII
  ConnectionImpl() = default;

  ConnectionImpl(ConnectionImpl const &) = delete;

  ConnectionImpl(ConnectionImpl &&) = delete;

  explicit ConnectionImpl(Timpl &&impl) : m_impl(::std::forward<Timpl>(impl)) {}

  ~ConnectionImpl() = default;

public:  // methods
  void clearWarnings() override final { m_impl.clearWarnings(); }

  void close() override final { m_impl.close(); }

  void commit() override final { m_impl.commit(); }

  bool isClosed() const override final { return m_impl.isClosed(); }

  bool isReadOnly() const override final { return m_impl.isReadOnly(); }

  void rollback() override final { m_impl.rollback(); }

public:  // operators
  ConnectionImpl<Timpl> &operator=(ConnectionImpl<Timpl> const &) = delete;

  ConnectionImpl<Timpl> &operator=(ConnectionImpl<Timpl> &&) = delete;
};

class Connection final {
private:  // variables
  ::std::unique_ptr<IConnectionImpl> m_impl;

public:  // RAII
  Connection() = delete;

  Connection(Connection const &) = delete;

  Connection(Connection &&) = default;

  template <typename Timpl>
  explicit Connection(Timpl &&impl)
      : m_impl(make_unique<ConnectionImpl<Timpl>>(::std::forward<Timpl>(impl))) {}

  ~Connection() {}

public:  // methods
  void clearWarnings() { m_impl->clearWarnings(); }

  void close() { m_impl->close(); }

  void commit() { m_impl->commit(); }

  bool isClosed() const { return m_impl->isClosed(); }

  bool isReadOnly() const { return m_impl->isReadOnly(); }

  void rollback() { m_impl->rollback(); }

public:  // operators
  Connection &operator=(Connection const &) = delete;

  Connection &operator=(Connection &&) = default;
};

}  // namespace cxxdbc

#endif  // INCLUDED_CXXDBC_CONNECTION_H
