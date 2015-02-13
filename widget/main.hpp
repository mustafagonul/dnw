#ifndef DNW_WIDGET_MAIN_HPP
#define DNW_WIDGET_MAIN_HPP

#include "widget/fwd.hpp"
#include "system/filesystem/config.hpp"
#include "system/filesystem/node.hpp"
#include "system/system.hpp"
#include "authentication/session.hpp"
#include <Wt/WContainerWidget>


namespace dnw {
  namespace widget {

    class Main : public Wt::WContainerWidget {
    private:
      using Config = dnw::system::filesystem::Config;
      using Node = dnw::system::filesystem::Node;
      using System = system::System;
      using Session = authentication::Session;
      using Parent = Wt::WContainerWidget;
      using Container = Wt::WContainerWidget;
      using Signal = Wt::Signal<>;

    public:
      explicit Main(Parent *parent = nullptr);
      virtual ~Main();

    private:
      void onRebuild();
      void onModeChange(Any const &);
      void onLanguageChange(Any const &);
      void onItemChange(Any const &);
      void onMain(Any const &);

    private:
      Config    config;
      Node      node;
      System    system;
      Session   session;
      Signal    rebuildSignal;

      Tree      *tree;
      Mode      *mode;
      Language  *language;
      Container *container;
      Widget    *workspace;

    };
  }
}


#endif // DNW_WIDGET_MAIN_HPP
