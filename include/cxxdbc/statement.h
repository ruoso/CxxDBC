#ifndef INCLUDED_CXXDBC_STATEMENT_H
#define INCLUDED_CXXDBC_STATEMENT_H

// CxxDBC includes
#include <cxxdbc/make_unique.h>

// third-party includes
#include <boost/utility/string_ref.hpp>

// standard includes
#include <memory>

namespace cxxdbc {

class IStatementImpl {
public:  // RAII
  virtual ~IStatementImpl() = default;

public:  // methods
  virtual void close() = 0;

  virtual bool execute(::boost::string_ref query) = 0;

  virtual bool isClosed() const = 0;
};

template <typename Timpl>
class StatementImpl : public IStatementImpl {
private:  // variables
  Timpl m_impl;

public:  // RAII
  StatementImpl() = default;

  StatementImpl(StatementImpl const &) = delete;

  StatementImpl(StatementImpl &&) = delete;

  explicit StatementImpl(Timpl &&impl) : m_impl(::std::forward<Timpl>(impl)) {}

  ~StatementImpl() = default;

public:  // methods
  void close() override final { m_impl.close(); }

  bool execute(::boost::string_ref query) override final { return m_impl.execute(query); }

  bool isClosed() const override final { return m_impl.isClosed(); }

public:  // operators
  StatementImpl<Timpl> &operator=(StatementImpl<Timpl> const &) = delete;

  StatementImpl<Timpl> &operator=(StatementImpl<Timpl> &&) = delete;
};

class Statement {
private:  // variables
  ::std::unique_ptr<IStatementImpl> m_impl;

public:  // RAII
  Statement() = delete;

  Statement(Statement const &) = delete;

  Statement(Statement &&) = default;

  template <typename Timpl>
  explicit Statement(Timpl &&impl)
      : m_impl(make_unique<StatementImpl<Timpl>>(::std::forward<Timpl>(impl))) {}

  ~Statement() {}

public:  // methods
  void close() { m_impl->close(); }

  bool execute(::boost::string_ref query) { return m_impl->execute(query); }

  bool isClosed() const { return m_impl->isClosed(); }
};

}  // namespace cxxdbc

#endif  // INCLUDED_CXXDBC_STATEMENT_H
