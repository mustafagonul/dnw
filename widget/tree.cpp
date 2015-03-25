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

#include "system/system.hpp"
#include "system/node.hpp"
#include "widget/tree.hpp"
#include "widget/content.hpp"
#include "field/name.hpp"
#include <Wt/WStandardItem>
#include <Wt/WColor>


namespace dnw {
namespace widget {


bool Tree::Comparator::operator()(Any const &a1, Any const &a2)
{
  auto s1 = boost::any_cast<String>(a1);
  auto s2 = boost::any_cast<String>(a2);

  return s1 < s2;
}

bool operator==(Any const &a1, Any const &a2)
{
  auto s1 = boost::any_cast<String>(a1);
  auto s2 = boost::any_cast<String>(a2);

  return s1 == s2;
}

Tree::Tree(System const &system, Parent *parent)
  : Widget(system, parent)
  , view(this)
  , model(this)
  , keys()
  , itemChangedSignal()
{
  view.clicked().connect(this, &Tree::onItemClick);
  view.doubleClicked().connect(this, &Tree::onItemDoubleClick);
  view.expanded().connect(this, &Tree::onExpanded);
  view.collapsed().connect(this, &Tree::onCollapsed);

  view.setModel(&model);
  view.setSelectionMode(Wt::SingleSelection);
  view.expandToDepth(1);
  view.setColumnBorder(Wt::WColor(Wt::black));
  view.setSortingEnabled(false);

  Tree::update();
}

Tree::~Tree()
{
}

void Tree::update()
{
  populateModel();
  expandModel();
}

Tree::Signal &Tree::itemChanged()
{
  return itemChangedSignal;
}

void Tree::onItemClick(Index index)
{
  if (index.isValid() == false)
    return;

  auto data = model.data(index, Wt::UserRole);
  auto key = boost::any_cast<String>(data);

  itemChanged().emit(key);
}

void Tree::onItemDoubleClick(Index index)
{
  if (index.isValid() == false)
    return;

  if (view.isExpanded(index))
    view.collapse(index);
  else
    view.expand(index);
}

void Tree::onExpanded(Index index)
{
  if (index.isValid() == false)
   return;

  using std::less;

  auto data = model.data(index, Wt::UserRole);
  auto key = boost::any_cast<String>(data);

  keys.insert(key);
}

void Tree::onCollapsed(Index index)
{
  if (index.isValid() == false)
    return;

  using std::less;

  auto data = model.data(index, Wt::UserRole);
  auto key = boost::any_cast<String>(data);

  keys.erase(key);
}

void Tree::populateModel()
{
  model.clear();
  model.insertColumn(0);
  model.setHeaderData(0, tr("Contents"));

  auto root = new Item();
  auto rootNode = system().root();
  auto rootKey = rootNode->rootKey();

  model.appendRow(root);

  populateItem(rootKey, *root);
}

void Tree::populateItem(Any const &key, Item &item)
{
  auto clone = system().node()->clone(key);
  if (clone == nullptr)
    return;

  auto name = String("   ") + field::Name(*clone).text(system().language());
  auto count = clone->nodeCount();

  item.setText(name);
  item.setData(key, Wt::UserRole);
  if (count == 0)
    item.setIcon("icons/document.png");
  else
    item.setIcon("icons/yellow-folder-open.png");

  for (unsigned i = 0; i < count; ++i) {
    auto nodeClone = clone->node(i);
    auto nodeKey = nodeClone->currentKey();
    auto nodeItem = new Item();

    item.appendRow(nodeItem);

    populateItem(nodeKey, *nodeItem);
  }
}

void Tree::expandModel()
{
  view.expanded().setBlocked(true);
  view.collapsed().setBlocked(true);

  keys.insert(system().key());

  auto root = model.item(0, 0);
  if (root == nullptr)
    return;

  expandItem(*root);

  view.expanded().setBlocked(false);
  view.collapsed().setBlocked(false);
}

void Tree::expandItem(Item &item)
{
  auto any = item.data();
  if (keys.find(any) == keys.end())
    view.collapse(item.index());
  else
    view.expand(item.index());

  if (any == system().key())
    view.select(item.index());

  auto count = item.rowCount();
  for (decltype(count) i = 0; i < count; ++i) {
    auto subItem = item.child(i, 0);
    expandItem(*subItem);
  }
}


} // widget
} // dnw
