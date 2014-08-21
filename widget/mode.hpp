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

#ifndef SITE_WIDGET_MODE_HPP
#define SITE_WIDGET_MODE_HPP

#include "widget/base.hpp"
#include <Wt/WToolBar>
#include <Wt/WPushButton>


namespace site {
  namespace widget {

    class Mode : public Base {
    private:
      using Toolbar    = Wt::WToolBar;
      using PushButton = Wt::WPushButton;

    public:
      Mode(String const &language, Parent * = nullptr);
      virtual ~Mode();

    public:
      virtual void update();

    private:
      void onAdmin();
      void onGuest();

    private:
      Toolbar toolbar;
      PushButton *guestButton;
      PushButton *adminButton;

    };

  }
}

#endif // SITE_WIDGET_MODE_HPP
