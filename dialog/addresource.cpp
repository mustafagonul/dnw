#include "dialog/addresource.hpp"
#include "utility/file.hpp"
#include "field/resource.hpp"
#include <Wt/WDialog>
#include <Wt/WFileUpload>
#include <Wt/WPushButton>
#include <Wt/WProgressBar>
#include <Wt/WMessageBox>


namespace dnw {
namespace dialog {


void addResource(String const &name, field::Resource const &resource)
{
  using Dialog = Wt::WDialog;
  using FileUpload = Wt::WFileUpload;
  using Button = Wt::WPushButton;
  using ProgressBar = Wt::WProgressBar;
  using MessageBox = Wt::WMessageBox;

  // Dialog
  Dialog dialog(name);
  dialog.setClosable(true);
  dialog.setResizable(true);
  dialog.rejectWhenEscapePressed();


  // File upload
  auto fileUpload = new FileUpload(dialog.contents());
  auto button = new Button("Add", dialog.contents());
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
    MessageBox::show("Admin", "Too Large!", Wt::Ok);
    dialog.reject();
  }));

  // Exec
  auto result = dialog.exec();
  if (result == Dialog::Accepted)
    MessageBox::show("Admin", "Added.", Wt::Ok);
}


} // dialog
} // dnw
