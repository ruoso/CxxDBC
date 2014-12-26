#ifndef INCLUDED_CXXDBC_1_0_PROPERTIES_H
#define INCLUDED_CXXDBC_1_0_PROPERTIES_H

// third-party includes
#include <boost/utility/string_ref.hpp>

// standard includes
#include <unordered_map>

namespace cxxdbc {
namespace v1_0 {

typedef unordered_map<boost::string_ref,boost::string_ref> Properties;

}  // namespace v1_0
}  // namespace cxxdbc

#endif  // INCLUDED_CXXDBC_1_0_PROPERTIES_H
