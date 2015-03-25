/*
 * Copyright (C) 2014 Mustafa Gönül
 *
 * dnw is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * dnw is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
**/

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
