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

#ifndef DNW_WIDGET_INDEX_HPP
#define DNW_WIDGET_INDEX_HPP

#include "widget/widget.hpp"


namespace dnw {
  namespace widget {

    class Index : public Widget {
    public:
      explicit Index(System const &system, Parent *parent = nullptr);
      virtual ~Index();

    public:
      virtual void update() final;
    };

  }
}


#endif // DNW_WIDGET_INDEX_HPP
