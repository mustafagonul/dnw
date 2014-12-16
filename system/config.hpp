#ifndef DNW_SYSTEM_CONFIG_HPP
#define DNW_SYSTEM_CONFIG_HPP

#include "utility/common.hpp"
#include <boost/optional.hpp>


namespace dnw {
  namespace system {

    class Config {
    protected:
      using OStr = boost::optional<String>;

    protected:
      Config();

      // TODO mustafa: special functions

    public:
      virtual ~Config() = 0;

    public:
      virtual Size count(String const &header) const = 0;
      virtual OStr value(String const &header, String const &property) const = 0;
      virtual OStr value(String const &header, Index index) const = 0;
      virtual OStr property(String const &header, Index index) const = 0;
      virtual void set(String const &header, String const &property, String const &value) = 0;
      virtual void set(String const &header, Index index, String const &value) = 0;
    };

  }
}


#endif // DNW_SYSTEM_CONFIG_HPP
