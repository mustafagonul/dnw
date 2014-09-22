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

#include "widget/base.hpp"
#include "system/fwd.hpp"
#include <boost/any.hpp>


namespace dnw {
  namespace widget {

    class Widget : public Base {
    protected:
      using Any    = boost::any;
      using Device = dnw::system::Device;

    protected:
      Widget(Device const &device,
             String const &language,
             Any const &key,
             Parent *parent = nullptr);

    public:
      virtual ~Widget() = 0;

    public:
      void setKey(Any const &);

    protected:
      Device const &device() const;
      Any const &key() const;

    private:
      Device const &m_device;
      Any m_key;
    };

  }
}


#endif // DNW_WIDGET_WIDGET_HPP
