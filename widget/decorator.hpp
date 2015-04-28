#ifndef DNW_WIDGET_DECORATOR_HPP
#define DNW_WIDGET_DECORATOR_HPP

#include "widget/widget.hpp"


namespace dnw {
  namespace widget {

    class Decorator : public Widget {
    private:
      using Container = Wt::WContainerWidget;

    protected:
      explicit Decorator(System const &system, Parent *parent = nullptr);

    public:
      virtual ~Decorator() = 0;

    public:
      virtual void update() override;
      virtual void regenerate() override;
      virtual void clear() override;

    protected:
      void addContainer();
      void setWidget(Widget *w);

    private:
      Container *container;
      Widget    *widget;
    };

  }
}


#endif // DNW_WIDGET_DECORATOR_HPP
