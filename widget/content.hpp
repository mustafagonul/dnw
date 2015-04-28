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

#ifndef DNW_WIDGET_CONTENT_HPP
#define DNW_WIDGET_CONTENT_HPP

#include "widget/widget.hpp"
#include "system/fwd.hpp"
#include <map>


namespace dnw {
  namespace widget {

    class Content : public Widget {
    private:
      using FileMap = std::map<String, String>;
      using Node = dnw::system::Node;

    public:
      explicit Content(System const &system, Parent *parent = nullptr);
      virtual ~Content();

    public:
      virtual void update() final;

    public:
      void onSearch(Any const &any);
      Signal &itemChanged();

    private:
      void createContent();
      void createShowAll();
      void createSearch(String const &str);
      void search(String const &str, Anys &results);
      void search(Node const &node, String const &str, Anys &results);

    private:
      FileMap fileMap;
      String  current;
      Signal  itemChangedSignal;
    };

  }
}


#endif // DNW_WIDGET_CONTENT_HPP
