#ifndef CXXDBC_TEST_NULLDRIVER_NULL_DRIVER_H
#define CXXDBC_TEST_NULLDRIVER_NULL_DRIVER_H

#include <cxxdbc/1.0/driver.h>

namespace cxxdbc {
namespace nulldriver {
using cxxdbc::v1_0::Driver;
using cxxdbc::v1_0::IDriver;
using cxxdbc::v1_0::DriverPropertyInfo;
using cxxdbc::v1_0::Properties;
using cxxdbc::v1_0::Connection;

class NullDriver : public IDriver {
public:
  bool acceptsURL(boost::string_ref url) const;
  Connection connect(boost::string_ref url, Properties info);
  int getMajorVersion() const;
  int getMinorVersion() const;
  std::vector<DriverPropertyInfo> getPropertyInfo(boost::string_ref url,
                                                  Properties info) const;
  int getSupportedCxxDBCMajorVersion() const;
  int getSupportedCxxDBCMinorVersion() const;
  bool isEqual(IDriver const &driver) const;
  bool isSQL() const;

  static Driver makeDriver() {
    std::shared_ptr<IDriver> wrapper(new cxxdbc::nulldriver::NullDriver());
    return Driver(std::move(wrapper));
  }
};

}
}


#endif // CXXDBC_TEST_NULLDRIVER_NULL_DRIVER_H
