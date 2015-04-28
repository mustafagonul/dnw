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

#include <dialog/select.hpp>
#include <Wt/WDialog>
#include <Wt/WSelectionBox>
#include <Wt/WPushButton>
#include <Wt/WRadioButton>
#include <Wt/WButtonGroup>


namespace dnw {
namespace dialog {

bool selectWithSelectionBox(String const &title, Strings const &strings, Index &current)
{
  using Dialog = Wt::WDialog;
  using SelectionBox = Wt::WSelectionBox;
  using Button = Wt::WPushButton;


  Dialog dialog{Dialog::tr(title)};

  auto selectionBox = new SelectionBox;
  auto okButton = new Button{Button::tr("Ok")};
  auto cancelButton = new Button{Button::tr("Cancel")};
  for (auto &str : strings)
    selectionBox->addItem(str);

  dialog.contents()->addWidget(selectionBox);
  dialog.contents()->addWidget(okButton);
  dialog.contents()->addWidget(cancelButton);

  okButton->clicked().connect(std::bind([&]{ dialog.accept(); }));
  cancelButton->clicked().connect(std::bind([&]{ dialog.reject(); }));

  auto result = dialog.exec();
  if (result == Dialog::Accepted) {
    current = selectionBox->currentIndex();
    return true;
  }

  return false;
}

bool selectWithButtonGroup(String const &title, Strings const &strings, Index &current)
{
  using Dialog = Wt::WDialog;
  using Button = Wt::WPushButton;
  using Radio = Wt::WRadioButton;
  using Group = Wt::WButtonGroup;

  Dialog dialog{Dialog::tr(title)};

  auto group = new Group{dialog.contents()};
  auto okButton = new Button{Button::tr("Ok")};
  auto cancelButton = new Button{Button::tr("Cancel")};

  for (auto &str : strings) {
    auto radio = new Radio;
    radio->setText(str);
    radio->setInline(false);
    group->addButton(radio);
  }

  group->setSelectedButtonIndex(current);

  dialog.contents()->addWidget(okButton);
  dialog.contents()->addWidget(cancelButton);

  okButton->clicked().connect(std::bind([&]{ dialog.accept(); }));
  cancelButton->clicked().connect(std::bind([&]{ dialog.reject(); }));

  auto result = dialog.exec();
  if (result == Dialog::Accepted) {
    current = group->selectedButtonIndex();
    return true;
  }

  return false;
}


} // dialog
} // dnw
