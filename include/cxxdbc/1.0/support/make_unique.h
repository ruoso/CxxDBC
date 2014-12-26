#ifndef INCLUDED_CXXDBC_1_0_SUPPORT_MAKE_UNIQUE_H
#define INCLUDED_CXXDBC_1_0_SUPPORT_MAKE_UNIQUE_H

// standard includes
#include <memory>

namespace cxxdbc {
namespace v1_0 {

/// Only defining this until C++14 is fully supported on all target compilers
template <typename Ttype, typename... Ttail>
::std::unique_ptr<Ttype> make_unique(Ttail&&... tail) {
  return ::std::unique_ptr<Ttype>(new Ttype(std::forward<Ttail>(tail)...));
}

}  // namespace v1_0
}  // namespace cxxdbc

#endif  // INCLUDED_CXXDBC_1_0_SUPPORT_MAKE_UNIQUE_H
