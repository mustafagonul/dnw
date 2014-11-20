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

#ifndef DNW_WIDGET_APPLICATION_HPP
#define DNW_WIDGET_APPLICATION_HPP

#include "widget/fwd.hpp"
#include "authentication/session.hpp"
#include "system/filesystem/device.hpp"
#include <Wt/WApplication>
#include <Wt/WPushButton>


namespace dnw {
  namespace widget {

    class Application : public Wt::WApplication {
    private:
      using Environment = Wt::WEnvironment;
      using Container   = Wt::WContainerWidget;
      using Device      = dnw::system::filesystem::Device;
      using Session     = dnw::authentication::Session;

    public:
      explicit Application(Environment const &);
      virtual ~Application();

    private:
      void onMode(Any const &);
      void onLanguage(Any const &);
      void onTree(Any const &);

      void update();
      bool setPasswordDialog();

    private:
      Device    device;
      Session   session;

      Tree      *tree;
      Mode      *mode;
      Language  *language;
      Container *container;
      Widget    *main;

      String currentLanguage;
      Any currentKey;
    };

  }
}


#endif // DNW_WIDGET_APPLICATION_HPP
