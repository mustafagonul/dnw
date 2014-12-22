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

#include "dialog/messagebox.hpp"
#include <Wt/WMessageBox>


namespace dnw {
namespace dialog {


void messageBox(String const &str, String const &message)
{
  Wt::WMessageBox messageBox(Wt::WString::tr(str),
                             Wt::WString::tr(message),
                             Wt::Information,
                             Wt::Ok);

  messageBox.buttonClicked().connect(std::bind([&]{
    messageBox.accept();
  }));

  messageBox.exec();
}

void errorMessageBox(String const &str)
{
  errorMessageBox(str, "Error!");
}

void errorMessageBox(String const &str, String const &message)
{
  Wt::WMessageBox messageBox(Wt::WString::tr(str),
                             Wt::WString::tr(message),
                             Wt::Warning,
                             Wt::Ok);

  messageBox.buttonClicked().connect(std::bind([&]{
    messageBox.accept();
  }));

  messageBox.exec();
}

bool booleanMessageBox(String const &str, String const &message)
{
  Wt::WMessageBox messageBox(Wt::WString::tr(str),
                             Wt::WString::tr(message),
                             Wt::Question,
                             Wt::Ok | Wt::Cancel);

  messageBox.buttonClicked().connect(std::bind([&]{
    if (messageBox.buttonResult() == Wt::Ok)
      messageBox.accept();
    else
      messageBox.reject();
  }));

  auto result = messageBox.exec();

  return result == Wt::WMessageBox::Accepted;
}


} // dialog
} // dnw
