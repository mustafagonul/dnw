#ifndef DNW_WIDGET_INDEX_HPP
#define DNW_WIDGET_INDEX_HPP

#include "widget/widget.hpp"


namespace dnw {
  namespace widget {

    class Index : public Widget {
    public:
      explicit Index(System const &system, Parent *parent = nullptr);
      virtual ~Index();

    public:
      virtual void update() final;
    };

  }
}


#endif // DNW_WIDGET_INDEX_HPP
