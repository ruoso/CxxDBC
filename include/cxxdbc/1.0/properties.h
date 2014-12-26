#ifndef INCLUDED_CXXDBC_1_0_PROPERTIES_H
#define INCLUDED_CXXDBC_1_0_PROPERTIES_H

// standard includes
#include <unordered_map>

// third-party includes
#include <boost/utility/string_ref.hpp>

// cxxdbc includes
#include <cxxdbc/1.0/support/string_ref_hash.h>

namespace cxxdbc {
namespace v1_0 {

typedef std::unordered_map<boost::string_ref,boost::string_ref> Properties;

}  // namespace v1_0
}  // namespace cxxdbc

#endif  // INCLUDED_CXXDBC_1_0_PROPERTIES_H
