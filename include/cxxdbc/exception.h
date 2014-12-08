#ifndef INCLUDED_CXXDBC_EXCEPTION_H
#define INCLUDED_CXXDBC_EXCEPTION_H

// third party includes
#include <boost/utility/string_ref.hpp>

// standard includes
#include <exception>

namespace cxxdbc {

class Exception : public ::std::exception {
private:  // variables
  ::std::string m_reason;
  ::std::string m_sqlState;
  int m_vendorCode;

public:  // RAII
  Exception() = delete;

  Exception(Exception const&) = default;

  Exception(Exception&&) = default;

  Exception(::boost::string_ref reason_, ::boost::string_ref sqlState_, int vendorCode_)
      : m_reason(reason_), m_sqlState(sqlState_), m_vendorCode(vendorCode_) {}

  Exception(::boost::string_ref reason_) : Exception(reason_, "", 0) {}

  Exception(::boost::string_ref reason_, ::boost::string_ref sqlState_)
      : Exception(reason_, sqlState_, 0) {}

  Exception(::boost::string_ref reason_, int vendorCode_) : Exception(reason_, "", vendorCode_) {}

  ~Exception() override final {}

public:  // methods
  ::boost::string_ref reason() const { return m_reason; }

  ::boost::string_ref sqlState() const { return m_sqlState; }

  int vendorCode() const { return m_vendorCode; }

  char const* what() const noexcept override final { return m_reason.c_str(); }

public:  // operators
  Exception& operator=(Exception const& rhs) {
    m_sqlState = rhs.m_sqlState;
    m_vendorCode = rhs.m_vendorCode;
    m_reason = rhs.m_reason;
    return *this;
  }
};

}  // namespace cxxdbc

#endif  // INCLUDED_CXXDBC_EXCEPTION_H
