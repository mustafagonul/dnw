#include "dialog/resource.hpp"
#include "field/resource.hpp"
#include <Wt/WTable>
#include <Wt/WCssDecorationStyle>
#include <Wt/WMessageBox>
#include <Wt/WText>
#include <Wt/WFileResource>
#include <Wt/WPushButton>


namespace dnw {
namespace dialog {


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
  using Text = Wt::WText;
  using Link = Wt::WLink;
  using Button = Wt::WPushButton;
  using FileResource = Wt::WFileResource;
  using MessageBox = Wt::WMessageBox;
  using Dialog = Wt::WDialog;


  auto count = resource.resourceCount();
  if (count == 0) {
    MessageBox messageBox(name, "Empty!", Wt::Warning, Wt::Ok);
    messageBox.exec();

    return;
  }

  Dialog dialog(name);
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


} // dialog
} // dnw

