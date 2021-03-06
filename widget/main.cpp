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

#include "widget/main.hpp"
#include "widget/navigationbar.hpp"
#include "widget/tree.hpp"
#include "widget/admin.hpp"
#include "widget/content.hpp"
#include "widget/index.hpp"
#include "dialog/password.hpp"
#include "system/system.hpp"
#include <Wt/WApplication>
#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>


namespace dnw {
namespace widget {


using HBoxLayout = Wt::WHBoxLayout;
using VBoxLayout = Wt::WVBoxLayout;


static void setLocale(String const &language)
{
  auto app = Wt::WApplication::instance();
  if (app == nullptr)
    return;

  app->setLocale(language);
}

static void setMessages()
{
  auto app = Wt::WApplication::instance();
  if (app == nullptr)
    return;

  app->messageResourceBundle().use("messages/general");
}

Main::Main(System &system_, Session &session_, Parent *parent)
  : system(system_)
  , session(session_)
  , navigationBar(nullptr)
  , tree(nullptr)
  , workspaceContainer(nullptr)
  , workspace(nullptr)
{
  // Language
  setMessages();
  setLocale(system.language());

  // Layout
  auto main = new HBoxLayout;
  auto right = new Container{this};
  auto left = new Container{this};

  // Items
  tree = new Tree{system, this};
  navigationBar = new NavigationBar{system, this};
  workspaceContainer = new Container{this};

  // Main
  auto content = new Content{system};
  workspace = content;
  workspaceContainer->setOverflow(Container::OverflowAuto);
  workspaceContainer->addWidget(workspace);

  // Layout settings
  setLayout(main);
  main->addWidget(right, 10);
  main->addStretch(1);
  main->addWidget(left, 40);
  right->addWidget(tree);
  left->addWidget(navigationBar);
  left->addWidget(workspaceContainer);

  // Connections
  content->itemChanged().connect(this, &Main::onItemChange);
  navigationBar->modeChanged().connect(this, &Main::onModeChange);
  navigationBar->languageChanged().connect(this, &Main::onLanguageChange);
  navigationBar->search().connect(content, &Content::onSearch);
  tree->itemChanged().connect(this, &Main::onItemChange);


  // Main update
  workspace->update();
}

Main::~Main()
{
}

void Main::update()
{
  // changes locale language
  setLocale(system.language()); // TODO mustafa: give a more proper name to this function

  // tree & navigation bar
  navigationBar->update();
  tree->update();

  // workspace
  if (workspace)
    workspace->update();
}

void Main::showIndex()
{
  auto index = new Index(system);

  setWorkspace(index);
}

void Main::showContent()
{
  auto content = new Content(system);
  content->itemChanged().connect(this, &Main::onItemChange);
  navigationBar->search().connect(content, &Content::onSearch);

  setWorkspace(content);
}

void Main::showAdmin()
{
  auto admin = new Admin(system);
  admin->itemChanged().connect(this, &Main::onItemChange);

  setWorkspace(admin);
}

void Main::onModeChange(Any const &any)
try
{
  // getting mode string
  auto mode = boost::any_cast<String>(any);

  // checks if there is a password
  if (dialog::checkPassword() == false)
    mode = "guest";

  // if the mode is admin, then asks for a password
  if (mode == "admin" && dialog::password(session) == false)
    mode = "guest";

  // guest mode flow
  if (mode == "guest") {
    showContent();

    return;
  }

  // admin mode flow
  if (mode == "admin") {
    showAdmin();

    return;
  }
}
catch (...) {
}

void Main::onLanguageChange(Any const &any)
try
{
  // changes system language
  auto lang = boost::any_cast<String>(any);
  system.setLanguage(lang);

  update();
}
catch (...) {
}

void Main::onItemChange(Any const &key)
{
  system.setKey(key);

  update();
}

void Main::setWorkspace(Widget *w)
{
  workspaceContainer->clear();
  workspace = w;

  if (workspace) {
    workspaceContainer->addWidget(workspace);
    workspace->update();
  }
}


} // widget
} // dnw
