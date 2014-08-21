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

#include "widget/tree.hpp"
#include "widget/content.hpp"
#include "system/device.hpp"
#include "field/name.hpp"
#include <Wt/WStandardItem>
#include <Wt/WColor>


namespace site {
namespace widget {


Tree::Tree(Device const &device,
           String const &language,
           Any const &key,
           Parent *parent)
  : Widget(device, language, key, parent)
  , view(this)
  , model(this)
{
  populateModel();

  view.setModel(&model);
  view.setSelectionMode(Wt::SingleSelection);
  view.expandToDepth(1);
  view.setColumnBorder(Wt::WColor(Wt::black));
  view.setSortingEnabled(false);

  view.clicked().connect(this, &Tree::onItemClick);
  view.doubleClicked().connect(this, &Tree::onItemDoubleClick);
}

Tree::~Tree()
{
}

void Tree::update()
{
  populateModel();

  Indexes indexes;
  index(indexes);
  for (auto index : indexes)
    view.expand(index);

  if (indexes.size())
    view.select(indexes.front());
}

void Tree::onItemClick(Index index)
{
  auto data = model.data(index, Wt::UserRole);
  auto key = boost::any_cast<String>(data);

  setKey(key);

  changed().emit(key);
}

void Tree::onItemDoubleClick(Index index)
{
  if (view.isExpanded(index))
    view.collapse(index);
  else
    view.expand(index);
}

void Tree::updateModel()
{

}

void Tree::updateItem(String const &key, Item &item)
{

}


void Tree::populateModel()
{
  model.clear();

  auto root = new Item();
  auto rootKey = device().rootKey();

  model.appendRow(root);

  populateItem(rootKey, *root);
}

void Tree::populateItem(Any const &key, Item &item)
{
  auto clone = device().clone(key);
  if (clone == nullptr)
    return;

  auto name = String("   ") + field::Name(*clone).name(language());
  auto count = clone->nodeCount();

  item.setText(name);
  item.setData(key, Wt::UserRole);
  if (count == 0)
    item.setIcon("icons/document.png");
  else
    item.setIcon("icons/yellow-folder-open.png");

  for (unsigned i = 0; i < count; ++i) {
    auto nodeClone = clone->nodeDevice(i);
    auto nodeKey = nodeClone->currentKey();
    auto nodeItem = new Item();

    item.appendRow(nodeItem);

    populateItem(nodeKey, *nodeItem);
  }
}

void Tree::expanded(Strings &result) const
{
  //view.
}

void Tree::expanded(Item const &item, Strings &result) const
{

}


bool Tree::index(Indexes &result) const
{
  result.clear();

  auto root = model.item(0, 0);
  if (root == nullptr)
    return false;

  return index(*root, result);
}

bool Tree::index(Item const &item, Indexes &result) const
{
  auto any = item.data();
  auto data = boost::any_cast<String>(any);
  auto keyStr = boost::any_cast<String>(key());


  if (data == keyStr) {
    result.push_back(item.index());

    return true;
  }

  for (int i = 0; i < item.rowCount(); ++i) {
    auto subItem = item.child(i, 0);
    if (index(*subItem, result)) {
      result.push_back(item.index());

      return true;
    }
  }

  return false;
}


} // widget
} // site
