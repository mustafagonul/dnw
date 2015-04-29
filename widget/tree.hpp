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

#ifndef DNW_WIDGET_TREE_HPP
#define DNW_WIDGET_TREE_HPP


#include "widget/widget.hpp"
#include <Wt/WTreeView>
#include <Wt/WStandardItemModel>
#include <set>


namespace dnw {
  namespace widget {

    class Tree : public Widget {
    private:
      struct Comparator {
        bool operator()(Any const &a1, Any const &a2);
      };

      using View    = Wt::WTreeView;
      using Model   = Wt::WStandardItemModel;
      using Item    = Wt::WStandardItem;
      using Index   = Wt::WModelIndex;
      using Indexes = Wt::WModelIndexList;
      using Keys    = std::set<Any, Comparator>;

    public:
      explicit Tree(System const &system, Parent *parent = nullptr);
      virtual ~Tree();

    public:
      virtual void update() final;

    public:
      Signal &itemChanged();

    private:
      void onItemClick(Index);
      void onItemDoubleClick(Index);
      void onExpanded(Index);
      void onCollapsed(Index);

      void createViewAndModel();
      void updateKeys();

      void populateModel();
      void populateItem(Any const &, Item &);
      void expandModel();
      void expandItem(Item &);



    private:
      View   *view;
      Model  *model;
      Keys   keys;

      Signal itemChangedSignal;
    };

  }
}

#endif // DNW_WIDGET_TREE_HPP
