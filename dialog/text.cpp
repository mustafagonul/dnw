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

#include "dialog/text.hpp"
#include "dialog/messagebox.hpp"
#include "field/text.hpp"
#include "utility/file.hpp"
#include <Wt/WDialog>
#include <Wt/WPushButton>
#include <Wt/WFileUpload>
#include <Wt/WProgressBar>


namespace dnw {
namespace dialog {


using Dialog = Wt::WDialog;
using Button = Wt::WPushButton;
using FileUpload = Wt::WFileUpload;
using ProgressBar = Wt::WProgressBar;


// TODO mustafa: remove this code
/*
void text(String const &language, field::Text const &text)
{
  Dialog dialog(name);
  dialog.setClosable(true);
  dialog.setResizable(true);
  dialog.rejectWhenEscapePressed();

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
*/

void uploadText(String const &language, field::Text const &text)
{
  // Dialog
  Dialog dialog(Dialog::tr("Upload"));
  dialog.setClosable(true);
  dialog.setResizable(true);
  dialog.rejectWhenEscapePressed();


  // File upload
  auto fileUpload = new FileUpload(dialog.contents());
  auto button = new Button(Button::tr("Upload"), dialog.contents());
  fileUpload->setProgressBar(new ProgressBar());
  fileUpload->setMultiple(false);
  fileUpload->setFilters("text/html");

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
      text.editText(language, str);
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


} // dialog
} // dnw



