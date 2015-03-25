#ifndef DNW_WIDGET_NAVIGATIONBAR_HPP
#define DNW_WIDGET_NAVIGATIONBAR_HPP

#include "widget/widget.hpp"
#include <Wt/WMenuItem>


namespace dnw {
  namespace widget {

    class NavigationBar : public Widget {
    public:
      explicit NavigationBar(System const &system, Parent *parent = nullptr);
      virtual ~NavigationBar();

    public:
      virtual void update() final;

    public:
      Signal &modeChanged();
      Signal &languageChanged();

    private:
      using Item = Wt::WMenuItem;

    private:
      Signal modeChangedSignal;
      Signal languageChangedSignal;
      Item  *languageItem;
      Item  *modeItem;
    };

  }
}


#endif // DNW_WIDGET_NAVIGATIONBAR_HPP
