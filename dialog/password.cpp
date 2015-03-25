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

#include "dialog/password.hpp"
#include "admin/password.hpp"
#include "authentication/session.hpp"
#include <Wt/WDialog>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/Auth/PasswordPromptDialog>


namespace dnw {
namespace dialog {


static bool setPassword()
{
  // Dialog
  Wt::WDialog dialog("Set Password"); // TODO mustafa: strings

  // PASS 1 Edit
  Wt::WLabel *passLabel1 = new Wt::WLabel("Password 1", dialog.contents()); // TODO mustafa: strings
  Wt::WLineEdit *passEdit1 = new Wt::WLineEdit(dialog.contents());
  passEdit1->setEchoMode(Wt::WLineEdit::Password);
  passLabel1->setBuddy(passEdit1);

  // PASS 2 Edit
  Wt::WLabel *passLabel2 = new Wt::WLabel("Password 2", dialog.contents()); // TODO mustafa: strings
  Wt::WLineEdit *passEdit2 = new Wt::WLineEdit(dialog.contents());
  passEdit2->setEchoMode(Wt::WLineEdit::Password);
  passLabel2->setBuddy(passEdit2);

  // Message
  Wt::WLabel *message = new Wt::WLabel(dialog.contents());

  // Push button
  Wt::WPushButton *ok = new Wt::WPushButton("OK", dialog.footer()); // TODO mustafa: strings
  ok->setDefault(true);
  ok->disable();

  // Check
  auto checkFunction = [&]{
    message->setText("");
    ok->disable();

    if (passEdit1->textSize() < 8) {
      message->setText("Password is too short!"); // TODO mustafa: strings
      return false;
    }

    if (passEdit1->text().value() != passEdit2->text().value()) {
      message->setText("Passwords do not match!"); // TODO mustafa: strings
      return false;
    }

    message->setText("OK!"); // TODO mustafa: strings
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

bool checkPassword()
{
  if (admin::passwordExists() == false)
    if (setPassword() == false)
      return false;

  return true;
}

bool password(authentication::Session &session)
{
  if (checkPassword() == false)
    return false;

  if (session.login().loggedIn() == false) {
    Wt::Auth::User user("admin", session.users());
    session.login().login(user, Wt::Auth::WeakLogin);
    Wt::Auth::PasswordPromptDialog promptDialog(session.login(), &session.authModel());

    auto dialogResult = promptDialog.exec();
    auto sessionResult = session.login().loggedIn();
    if (dialogResult == Wt::Auth::PasswordPromptDialog::Rejected ||
        sessionResult == false) {
      session.login().logout();
      return false;
    }
  }

  return true;
}


} // dialog
} // dnw

