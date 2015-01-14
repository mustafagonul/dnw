#ifndef DNW_WT_STRINGRESOURCE_HPP
#define DNW_WT_STRINGRESOURCE_HPP

#include "utility/common.hpp"
#include <Wt/WStreamResource>


namespace dnw {
  namespace wt {

    class StringResource : public Wt::WStreamResource {
    private:
      using Parent = Wt::WObject;

    public:
      explicit StringResource(Parent *parent = nullptr);
      virtual ~StringResource();

    public:
      virtual void handleRequest(Wt::Http::Request const &request, Wt::Http::Response &response) override;

    public:
      void setString(String const &str);

    private:
      String m_string;
    };




  }
}


#endif // DNW_WT_STRINGRESOURCE_HPP
