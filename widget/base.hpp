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

#ifndef DNW_WIDGET_BASE_HPP
#define DNW_WIDGET_BASE_HPP

#include <Wt/WContainerWidget>
#include <boost/any.hpp>


namespace dnw {
  namespace widget {

    class Base : public Wt::WContainerWidget {
    protected:
      using Parent = Wt::WContainerWidget;
      using Signal = Wt::Signal<boost::any>;
      using String = std::string;

    protected:
      Base(String const &language, Parent *parent = nullptr);

    public:
      virtual ~Base() = 0;

    public:
      virtual void update() = 0;

    public:
      void setLanguage(String const &);

    public:
      Signal &changed();

    protected:
      String const &language() const;

    private:
      String m_language;
      Signal m_changed;
    };

  }
}


#endif // DNW_WIDGET_BASE_HPP
