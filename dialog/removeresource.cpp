#include "dialog/removeresource.hpp"
#include "field/resource.hpp"
#include <Wt/WMessageBox>
#include <Wt/WDialog>
#include <Wt/WSelectionBox>
#include <Wt/WPushButton>


namespace dnw {
namespace dialog {


void removeResource(String const &name, field::Resource const &resource)
{
  using MessageBox = Wt::WMessageBox;
  using Dialog = Wt::WDialog;
  using SelectionBox = Wt::WSelectionBox;
  using Button = Wt::WPushButton;


  auto count = resource.resourceCount();
  if (count < 1) {
    MessageBox::show("Admin", "There is nothing to remove!", Wt::Ok);
    return;
  }

  // Dialog
  Dialog dialog("Add File");
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
  auto button = new Button("Remove", dialog.contents());
  button->clicked().connect(std::bind([&] {
    auto result = MessageBox::show("Admin", "Do you want to remove?", Wt::Ok | Wt::Cancel);

    if (result == Wt::Ok)
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
    MessageBox::show("Admin", "Removed.", Wt::Ok);
}


} // dialog
} // dnw
