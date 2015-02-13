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

#ifndef DNW_WIDGET_WIDGET_HPP
#define DNW_WIDGET_WIDGET_HPP

#include "utility/common.hpp"
#include "system/fwd.hpp"
#include <Wt/WContainerWidget>


namespace dnw {
  namespace widget {

    class Widget : public Wt::WContainerWidget {
    protected:
      using System = dnw::system::System;
      using Parent = Wt::WContainerWidget;
      using Signal = Wt::Signal<Any>;

    protected:
      Widget(System const &system, Parent *parent = nullptr);

    public:
      virtual ~Widget() = 0;

    public:
      virtual void update() = 0;

    public:
      // Signal &changed();

    protected:
      System const &system() const;

    private:
      System const &m_system;
      // Signal m_changed;
    };

  }
}


#endif // DNW_WIDGET_SYSTEM_HPP
