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

#include "widget/navigationbar.hpp"
#include "system/system.hpp"
#include "system/node.hpp"
#include "field/name.hpp"
#include <Wt/WNavigationBar>
#include <Wt/WPopupMenu>
#include <Wt/WText>
#include <Wt/WLineEdit>
#include <Wt/WAnchor>
#include <Wt/WLink>
#include <Wt/WApplication>
#include <Wt/WEnvironment>


namespace dnw {
namespace widget {


using Bar = Wt::WNavigationBar;
using Menu = Wt::WMenu;
using PopupMenu = Wt::WPopupMenu;
using Item = Wt::WMenuItem;
using LineEdit = Wt::WLineEdit;
using Text = Wt::WText;
using Link = Wt::WLink;


NavigationBar::NavigationBar(System const &system, Parent *parent)
  : Widget(system, parent)
  , modeChangedSignal()
  , languageChangedSignal()
  , languageItem(nullptr)
  , modeItem(nullptr)
{
  // bar & menus
  auto bar = new Bar{this};
  auto searchEdit = new LineEdit;
  auto contentsMenu = new Menu;
  auto languageMenu = new Menu;
  auto modeMenu = new Menu;
  searchEdit->setEmptyText(tr("Search"));
  bar->setResponsive(true);
  bar->addSearch(searchEdit);
  bar->addMenu(contentsMenu);
  bar->addMenu(languageMenu);
  bar->addMenu(modeMenu);


  // items
  languageItem = new Item{""};
  modeItem = new Item{""};
  Link contentsLink(Link::InternalPath, "/index");
  contentsMenu->addItem("Index", new Text(tr("Index")))->setLink(contentsLink);
  contentsMenu->itemAt(0)->setSelectable(false);
  languageMenu->addItem(languageItem);
  modeMenu->addItem(modeItem);

  // popup menus
  auto languagePopup = new PopupMenu;
  auto modePopup = new PopupMenu;
  languageItem->setMenu(languagePopup);
  modeItem->setMenu(modePopup);

  // languages
  languageItem->setText(system.languageStr());
  auto count = system.languageCount();
  for (decltype(count) i = 0; i < count; ++i) {
    auto str = system.languageStr(i);
    auto tag = system.languageTag(i);
    auto item = new Item(str);
    languagePopup->addItem(item);
    item->clicked().connect(std::bind([this](String const &tag, String const &str) {
      languageChanged().emit(tag);
      languageItem->setText(str);
    }, tag, str));
  }

  // modes
  auto guestItem = new Item{""};
  auto adminItem = new Item{""};
  modeItem->setText(tr("Guest"));
  guestItem->setText(tr("Guest"));
  adminItem->setText(tr("Admin"));
  modePopup->addItem(guestItem);
  modePopup->addItem(adminItem);
  guestItem->clicked().connect(std::bind([this]{
    modeChanged().emit(String{"guest"});
    modeItem->setText(tr("Guest"));
  }));
  adminItem->clicked().connect(std::bind([this]{
    modeChanged().emit(String{"admin"});
    modeItem->setText(tr("Admin"));
  }));

  // search
  searchEdit->enterPressed().connect(std::bind([this, searchEdit]{
    auto str = searchEdit->text().toUTF8();
    if (str.empty())
      return;

    search().emit(str);
  }));
}

NavigationBar::~NavigationBar()
{
}

void NavigationBar::update()
{
}

NavigationBar::Signal &NavigationBar::modeChanged()
{
  return modeChangedSignal;
}

NavigationBar::Signal &NavigationBar::languageChanged()
{
  return languageChangedSignal;
}

NavigationBar::Signal &NavigationBar::search()
{
  return searchSignal;
}


} // widget
} // dnw
