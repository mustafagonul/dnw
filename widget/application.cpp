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
#include "system/system.hpp"
#include "admin/password.hpp"
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WBootstrapTheme>
#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include <Wt/WBreak>
#include <Wt/Auth/PasswordPromptDialog>
#include <Wt/Auth/Login>
#include <Wt/Auth/AuthModel>



namespace dnw {
namespace widget {


Application::Application(System &sys, Environment const &env)
  : Wt::WApplication(env)
  , system(sys)
  , session()
  , tree(nullptr)
  , mode(nullptr)
  , language(nullptr)
  , container(nullptr)
  , main(nullptr)
{
  // UTF8
  Wt::WString::setDefaultEncoding(Wt::UTF8);

  // Theme
  setTheme(new Wt::WBootstrapTheme());

  // Title
  setTitle("Dnw");


  // Layouts
  auto mainLayout = new Wt::WHBoxLayout();
  auto leftLayout = new Wt::WVBoxLayout();
  auto rightLayout = new Wt::WVBoxLayout();
  auto topLayout = new Wt::WHBoxLayout();
  auto bottomLayout = new Wt::WVBoxLayout();


  // Items
  container = new Container(root());
  tree = new Tree(system, root());
  mode = new Mode(system, root());
  language = new Language(system, root());

  // main
  main = new Content(system);
  container->setOverflow(Container::OverflowAuto);
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
  tree->changed().connect(this, &Application::onKey);

  // Main update
  main->update();
}

Application::~Application()
{
}

void Application::onMode(Any const &any)
try
{
  auto mode = boost::any_cast<String>(any);

  if (admin::passwordExists() == false)
    if (setPasswordDialog() == false)
      mode = "guest";

  if (mode == "admin" && session.login().loggedIn() == false) {
    Wt::Auth::User user("admin", session.users());
    session.login().login(user, Wt::Auth::WeakLogin);
    Wt::Auth::PasswordPromptDialog promptDialog(session.login(), &session.authModel());

    if (promptDialog.exec() == Wt::Auth::PasswordPromptDialog::Rejected ||
        session.login().loggedIn() == false) {
      session.login().logout();
      mode = "guest";
    }
  }

  if (mode == "guest") {
    container->clear();

    main = new Content(system);
    container->addWidget(main);
    main->update();

    return;
  }

  if (mode == "admin") {
    container->clear();

    main = new Admin(system);
    container->addWidget(main);
    main->update();
    main->changed().connect(this, &Application::onKey);

    return;
  }
}
catch (...) {
}

void Application::onLanguage(Any const &any)
try
{
  auto lang = boost::any_cast<String>(any);

  system.setLanguage(lang);

  mode->update();
  tree->update();
  main->update();
  language->update();
}
catch (...) {
}

void Application::onKey(Any const &key)
{
  system.setKey(key);

  tree->update();
  main->update();
}

void Application::update()
{

}

bool Application::setPasswordDialog()
{
  // Dialog
  Wt::WDialog dialog("Set Password");

  // PASS 1 Edit
  Wt::WLabel *passLabel1 = new Wt::WLabel("Password 1", dialog.contents());
  Wt::WLineEdit *passEdit1 = new Wt::WLineEdit(dialog.contents());
  passEdit1->setEchoMode(Wt::WLineEdit::Password);
  passLabel1->setBuddy(passEdit1);

  // PASS 2 Edit
  Wt::WLabel *passLabel2 = new Wt::WLabel("Password 2", dialog.contents());
  Wt::WLineEdit *passEdit2 = new Wt::WLineEdit(dialog.contents());
  passEdit2->setEchoMode(Wt::WLineEdit::Password);
  passLabel2->setBuddy(passEdit2);

  // Message
  Wt::WLabel *message = new Wt::WLabel(dialog.contents());

  // Push button
  Wt::WPushButton *ok = new Wt::WPushButton("OK", dialog.footer());
  ok->setDefault(true);
  ok->disable();

  // Check
  auto checkFunction = [&]{
    message->setText("");
    ok->disable();

    if (passEdit1->textSize() < 8) {
      message->setText("Password is too short!");
      return false;
    }

    if (passEdit1->text().value() != passEdit2->text().value()) {
      message->setText("Passwords do not match!");
      return false;
    }

    message->setText("OK!");
    ok->enable();

    return true;
  };

  passEdit1->changed().connect(std::bind(checkFunction));
  passEdit2->changed().connect(std::bind(checkFunction));
  ok->clicked().connect(&dialog, &Wt::WDialog::accept);

  /*
   * Process the dialog result.
   */
  dialog.finished().connect(std::bind([&] () {
    if (dialog.result() == Wt::WDialog::Accepted) {
      auto pass = passEdit1->text().toUTF8();

      admin::setPassword(pass);
    }
  }));

  auto result = dialog.exec();
  if (result == Wt::WDialog::Accepted)
    return true;

  return false;
}


} // widget
} // dnw
