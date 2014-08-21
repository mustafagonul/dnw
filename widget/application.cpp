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

#include "widget/application.hpp"
#include "widget/admin.hpp"
#include "widget/language.hpp"
#include "widget/mode.hpp"
#include "widget/tree.hpp"
#include "widget/content.hpp"
#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include <Wt/WBreak>
#include <Wt/Auth/PasswordPromptDialog>
#include <Wt/Auth/Login>
#include <Wt/Auth/AuthModel>


namespace site {
namespace widget {


Application::Application(Environment const &env)
  : Wt::WApplication(env)
  , device()
  , tree(nullptr)
  , mode(nullptr)
  , language(nullptr)
  , container(nullptr)
  , main(nullptr)
  , currentLanguage("en")
  , currentKey()
{
  // Setting key
  currentKey = device.currentKey();

  // UTF8
  Wt::WString::setDefaultEncoding(Wt::UTF8);


  // Title
  setTitle("Documentator");


  // Layouts
  auto mainLayout = new Wt::WHBoxLayout();
  auto leftLayout = new Wt::WVBoxLayout();
  auto rightLayout = new Wt::WVBoxLayout();
  auto topLayout = new Wt::WHBoxLayout();
  auto bottomLayout = new Wt::WVBoxLayout();


  // Items
  container = new Container(root());
  tree = new Tree(device, currentLanguage, currentKey, root());
  mode = new Mode(currentLanguage, root());
  language = new Language(currentLanguage, root());

  // main
  main = new Content(device, currentLanguage, currentKey, root());
  container->addWidget(main);


  // Layout settings
  root()->setLayout(mainLayout);
  mainLayout->addLayout(leftLayout, 1);
  mainLayout->addLayout(rightLayout, 4);
  leftLayout->addWidget(tree);
  rightLayout->addLayout(topLayout);
  rightLayout->addWidget(new Wt::WBreak(root()));
  rightLayout->addWidget(new Wt::WBreak(root()));
  rightLayout->addWidget(new Wt::WBreak(root()));
  rightLayout->addWidget(new Wt::WBreak(root()));
  rightLayout->addLayout(bottomLayout, 1, Wt::AlignTop);
  topLayout->addWidget(language, 1, Wt::AlignLeft);
  topLayout->addWidget(mode, 1, Wt::AlignRight);
  bottomLayout->addWidget(container);


  // Connections
  mode->changed().connect(this, &Application::onMode);
  language->changed().connect(this, &Application::onLanguage);
  tree->changed().connect(this, &Application::onTree);
}

Application::~Application()
{
}

void Application::onMode(Any const &any)
try
{
  auto mode = boost::any_cast<String>(any);

  if (mode == "guest") {
    container->clear();

    main = new Content(device, currentLanguage, currentKey, root());
    container->addWidget(main);
    main->update();

    return;
  }

  if (mode == "admin") {
    container->clear();

    main = new Admin(device, currentLanguage, currentKey, root());
    container->addWidget(main);
    main->update();

    return;
  }
}
catch (...) {
}

void Application::onLanguage(Any const &any)
try
{
  auto lang = boost::any_cast<String>(any);

  currentLanguage = lang;

  mode->setLanguage(lang);
  tree->setLanguage(lang);
  main->setLanguage(lang);
  language->setLanguage(lang);

  mode->update();
  tree->update();
  main->update();
  language->update();
}
catch (...) {
}

void Application::onTree(Any const &key)
{
  currentKey = key;

  main->setKey(key);

  main->update();
}

void Application::update()
{

}


} // widget
} // site
