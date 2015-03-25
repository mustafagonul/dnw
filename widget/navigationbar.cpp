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


NavigationBar::NavigationBar(System const &system, Parent *parent)
  : Widget(system, parent)
  , modeChangedSignal()
  , languageChangedSignal()
  , languageItem(nullptr)
  , modeItem(nullptr)
{
  // bar & menus
  auto bar = new Bar{this};
  auto languageMenu = new Menu;
  auto modeMenu = new Menu;
  auto searchEdit = new LineEdit;
  searchEdit->setEmptyText(tr("Search"));
  bar->setResponsive(true);
  bar->addMenu(languageMenu);
  bar->addMenu(modeMenu);
  bar->addSearch(searchEdit);



  // items
  languageItem = new Item{""};
  modeItem = new Item{""};
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


} // widget
} // dnw
