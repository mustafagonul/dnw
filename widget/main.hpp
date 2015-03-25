#ifndef DNW_WIDGET_MAIN_HPP
#define DNW_WIDGET_MAIN_HPP

#include "widget/fwd.hpp"
#include "system/fwd.hpp"
#include "authentication/fwd.hpp"
#include "utility/common.hpp"
#include <Wt/WContainerWidget>


namespace dnw {
  namespace widget {

    class Main : public Wt::WContainerWidget {
    private:
      using Parent = Wt::WContainerWidget;
      using Container = Wt::WContainerWidget;
      using System = dnw::system::System;
      using Session = dnw::authentication::Session;

    public:
      Main(System &system,
           Session &session,
           Parent *parent = nullptr);
      virtual ~Main();

    private:
      void onModeChange(Any const &);
      void onLanguageChange(Any const &);
      void onItemChange(Any const &);

    private:
      System    &system;
      Session   &session;

      NavigationBar *navigationBar;
      Tree          *tree;
      Container     *workspaceContainer;
      Widget        *workspace;
    };
  }
}


#endif // DNW_WIDGET_MAIN_HPP
