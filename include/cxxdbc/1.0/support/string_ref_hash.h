#ifndef INCLUDED_CXXDBC_1_0_SUPPORT_STRING_REF_HASH_H
#define INCLUDED_CXXDBC_1_0_SUPPORT_STRING_REF_HASH_H

// standard includes
#include <memory>

// third-party includes
#include <boost/functional/hash.hpp>
#include <boost/utility/string_ref.hpp>

namespace std {
template <>
struct hash<boost::string_ref> {
  size_t operator()(boost::string_ref const& sr) const {
    return boost::hash_range(sr.begin(), sr.end());
  }
};
}

#endif  // INCLUDED_CXXDBC_SUPPORT_MAKE_UNIQUE_H
