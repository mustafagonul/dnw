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

#ifndef DNW_WIDGET_LANGUAGE_HPP
#define DNW_WIDGET_LANGUAGE_HPP

#include "widget/widget.hpp"
#include <Wt/WToolBar>
#include <Wt/WPushButton>
#include <map>


namespace dnw {
  namespace widget {

    class Language : public Widget {
    private:
      using Toolbar     = Wt::WToolBar;
      using PushButton  = Wt::WPushButton;
      using PushButtons = std::map<PushButton *, String>;

    public:
      Language(System const &system, Parent * = nullptr);
      virtual ~Language();

    public:
      virtual void update() final;

    public:
      Signal &languageChanged();

    private:
      Toolbar     m_toolbar;
      PushButtons m_pushbuttons;
      Signal      m_languageChanged;
    };

  }
}

#endif // DNW_WIDGET_LANGUAGE_HPP
