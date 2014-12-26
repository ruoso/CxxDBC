#ifndef INCLUDED_CXXDBC_1_0_DRIVER_PROPERTY_INFO_H
#define INCLUDED_CXXDBC_1_0_DRIVER_PROPERTY_INFO_H

// third-party includes
#include <boost/utility/string_ref.hpp>

namespace cxxdbc {
namespace v1_0 {

class DriverPropertyInfo {
private:
  DriverPropertyInfoImpl* impl;
public:
  DriverPropertyInfo(boost::string_ref name,
                     boost::string_ref value);
  DriverPropertyInfo(boost::string_ref name,
                     boost::string_ref value,
                     boost::string_ref description);
  DriverPropertyInfo(boost::string_ref name,
                     boost::string_ref value,
                     boost::string_ref description,
                     bool required);
  DriverPropertyInfo(boost::string_ref name,
                     boost::string_ref value,
                     boost::string_ref description,
                     bool required);
  DriverPropertyInfo(boost::string_ref name,
                     boost::string_ref value,
                     boost::string_ref description,
                     bool required,
                     std::vector<boost::string_ref> choices);
  virtual ~DriverPropertyInfo() = default;

  boost::string_ref getName();
  boost::string_ref getDescription();
  boost::string_ref getValue();
  bool isRequired();
  std::vector<boost::string_ref> getChoices();
}

}  // namespace v1_0
}  // namespace cxxdbc

#endif  // INCLUDED_CXXDBC_1_0_DRIVER_PROPERTY_INFO_H
