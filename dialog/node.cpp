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

#include "dialog/node.hpp"
#include "dialog/messagebox.hpp"
#include "system/device.hpp"
#include "field/name.hpp"
#include <Wt/WDialog>
#include <Wt/WSelectionBox>
#include <Wt/WPushButton>
#include <functional>


namespace dnw {
namespace dialog {


using Dialog = Wt::WDialog;
using SelectionBox = Wt::WSelectionBox;
using Button = Wt::WPushButton;
using Operation = std::function<bool(system::Device const &, Index)>;

static bool operate(system::Device const &device,
                    String const &language,
                    String const &str,
                    String const &question,
                    Operation operation)
{
  if (device.nodeCount() == 0) {
    errorMessageBox("Admin", "There is no node!");
    return false;
  }

  // Dialog
  Dialog dialog(str);
  dialog.setClosable(true);
  dialog.setResizable(true);
  dialog.rejectWhenEscapePressed();


  // Selection box
  auto selectionBox = new SelectionBox(dialog.contents());
  auto nodeCount = device.nodeCount();
  for (decltype(nodeCount) i = 0; i < nodeCount; ++i) {
    auto sub = device.nodeDevice(i);

    field::Name name(*sub);
    auto str = name.name(language);
    if (str.empty())
      str = "-------"; // TODO mustafa:

    selectionBox->addItem(str);
  }
  selectionBox->setCurrentIndex(0);

  // Ok push button
  auto ok = new Button("Ok", dialog.contents());
  ok->clicked().connect(std::bind([&] {
    auto result = booleanMessageBox("Admin", question);
    if (result)
      dialog.accept();
    else
      dialog.reject();
  }));

  // Accepted
  dialog.finished().connect(std::bind([&] {
    if (dialog.result() != Dialog::Accepted)
      return;

    auto current = static_cast<decltype(nodeCount)>(selectionBox->currentIndex());

    operation(device, current);
  }));

  // Exec
  auto result = dialog.exec();
  if (result == Dialog::Accepted)
    return true;

  return false;
}

bool removeNode(system::Device const &device, String const &language)
{
  auto op = [](system::Device const &device, Index index) -> bool {
    device.removeNode(index);
  };

  return operate(device, language, "Remove Node", "Do you want to remove node?", op);
}

bool moveNodeUp(system::Device const &device, String const &language)
{
  auto op = [](system::Device const &device, Index index) -> bool {
    device.moveNodeUp(index);
  };

  return operate(device, language, "Move Node Up", "Do you want to move node up?", op);
}

bool moveNodeDown(system::Device const &device, String const &language)
{
  auto op = [](system::Device const &device, Index index) -> bool {
    device.moveNodeDown(index);
  };

  return operate(device, language, "Move Node Down", "Do you want to move node down?", op);
}


} // dialog
} // dnw
