#ifndef DNW_WIDGET_SUSPICIOUS_HPP
#define DNW_WIDGET_SUSPICIOUS_HPP

#include "widget/widget.hpp"


namespace dnw {
  namespace widget {

    class Suspicious : public Widget {
    public:
      explicit Suspicious(System const &system, Parent *parent = nullptr);
      virtual ~Suspicious();

    public:
      virtual void update() final;

    public:
      Signal &itemChanged();

    private:
      Signal itemChangedSignal;
    };

  }
}


#endif // DNW_WIDGET_SUSPICIOUS_HPP
