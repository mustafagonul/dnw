#ifndef SYSTEM_FILESYSTEM_CONFIG_HPP
#define SYSTEM_FILESYSTEM_CONFIG_HPP

#include "system/config.hpp"


namespace dnw {
  namespace system {
    namespace filesystem {

      class Config : public dnw::system::Config {
      public:
        Config();
        virtual ~Config();

      public:
        virtual Size count(String const &header) const override;
        virtual OStr value(String const &header, String const &property) const override;
        virtual OStr value(String const &header, Index index) const override;
        virtual OStr property(String const &header, Index index) const override;
        virtual void set(String const &header, String const &property, String const &value) override;
        virtual void set(String const &header, Index index, String const &value) override;
      };

    }
  }
}

#endif /* SYSTEM_FILESYSTEM_CONFIG_HPP_ */
