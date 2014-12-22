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

#include "dialog/resource.hpp"
#include "dialog/messagebox.hpp"
#include "field/resource.hpp"
#include "utility/file.hpp"
#include <Wt/WTable>
#include <Wt/WCssDecorationStyle>
#include <Wt/WMessageBox>
#include <Wt/WText>
#include <Wt/WFileResource>
#include <Wt/WPushButton>
#include <Wt/WDialog>
#include <Wt/WFileUpload>
#include <Wt/WProgressBar>
#include <Wt/WSelectionBox>


namespace dnw {
namespace dialog {


using Text = Wt::WText;
using Link = Wt::WLink;
using Button = Wt::WPushButton;
using FileResource = Wt::WFileResource;
using Dialog = Wt::WDialog;
using FileUpload = Wt::WFileUpload;
using Button = Wt::WPushButton;
using ProgressBar = Wt::WProgressBar;
using Dialog = Wt::WDialog;
using SelectionBox = Wt::WSelectionBox;
using Button = Wt::WPushButton;


static void prepareTable(Wt::WTable *table)
{
  table->setHeaderCount(1);
  table->setWidth("100%");

  Wt::WCssDecorationStyle style;
  Wt::WBorder border(Wt::WBorder::Solid, Wt::WBorder::Thin, Wt::black);
  style.setBorder(border);
  table->setDecorationStyle(style);
}


void resource(String const &name, field::Resource const &resource)
{
  auto count = resource.resourceCount();
  if (count == 0) {
    errorMessageBox(name, "Empty!");
    return;
  }

  Dialog dialog(Dialog::tr(name));
  dialog.setClosable(true);
  dialog.setResizable(true);
  dialog.rejectWhenEscapePressed();

  auto files = new Wt::WTable(dialog.contents());
  prepareTable(files);

  // files
  files->clear();
  files->elementAt(0, 0)->addWidget(new Text(name));

  for (decltype(count) i = 0; i < count; ++i) {
    auto fileResource = new FileResource(resource.resourcePath(i), dialog.contents());
    auto str = resource.resourceName(i);
    auto button = new Button();
    Link link(fileResource);

    fileResource->suggestFileName(str);
    button->setText(str);
    button->setLink(link);

    files->elementAt(i + 1, 0)->addWidget(button);
  }

  dialog.exec();
}

void addResource(String const &name, field::Resource const &resource)
{
  // Dialog
  Dialog dialog(Dialog::tr(name));
  dialog.setClosable(true);
  dialog.setResizable(true);
  dialog.rejectWhenEscapePressed();


  // File upload
  auto fileUpload = new FileUpload(dialog.contents());
  auto button = new Button(Button::tr("Add"), dialog.contents());
  fileUpload->setProgressBar(new ProgressBar());
  fileUpload->setMultiple(false);

  // Button clicked
  button->clicked().connect(std::bind([&] {
    fileUpload->upload();
    button->disable();
  }));

  // Resource uploaded
  fileUpload->uploaded().connect(std::bind([&] {
    auto files = fileUpload->uploadedFiles();
    for (auto &f : files) {
      using dnw::utility::file::read;

      auto str = read(f.spoolFileName());
      resource.editResource(f.clientFileName(), str);
    }

    dialog.accept();
  }));

  // File length error
  fileUpload->fileTooLarge().connect(std::bind([&] {
    errorMessageBox("Admin", "Too Large!");
    dialog.reject();
  }));

  // Exec
  auto result = dialog.exec();
  if (result == Dialog::Accepted)
    messageBox("Admin", "Added.");
}

void removeResource(String const &name, field::Resource const &resource)
{
  auto count = resource.resourceCount();
  if (count < 1) {
    errorMessageBox("Admin", "There is nothing to remove!");
    return;
  }

  // Dialog
  Dialog dialog(Dialog::tr(name));
  dialog.setClosable(true);
  dialog.setResizable(true);
  dialog.rejectWhenEscapePressed();

  // Selection box
  auto selectionBox = new SelectionBox(dialog.contents());
  for (decltype(count) i = 0; i < count; ++i) {
    auto str = resource.resourceName(i);
    selectionBox->addItem(str);
  }
  selectionBox->setCurrentIndex(0);

  // Remove button
  auto button = new Button(Button::tr("Remove"), dialog.contents());
  button->clicked().connect(std::bind([&] {
    auto result = booleanMessageBox("Admin", "Do you want to remove?");
    if (result)
      dialog.accept();
  }));

  // Accepted
  dialog.finished().connect(std::bind([&] {
    if (dialog.result() != Dialog::Accepted)
      return;

    auto current = static_cast<decltype(count)>(selectionBox->currentIndex());
    auto str = resource.resourceName(current);
    resource.removeResource(str);
  }));

  auto result = dialog.exec();
  if (result == Dialog::Accepted)
    messageBox("Admin", "Removed.");
}


} // dialog
} // dnw

