#include "widget/editor.hpp"
#include "system/system.hpp"
#include "system/node.hpp"
#include "dialog/messagebox.hpp"
#include "dialog/resource.hpp"
#include "dialog/text.hpp"
#include "dialog/select.hpp"
#include "field/name.hpp"
#include "field/content.hpp"
#include "field/code.hpp"
#include "field/file.hpp"
#include "utility/string.hpp"
#include <Wt/WTabWidget>
#include <Wt/WToolBar>
#include <Wt/WPushButton>
#include <Wt/WBreak>
#include <Wt/WTextEdit>
#include <Wt/WFileResource>
#include <Wt/Utils>


namespace dnw {
namespace widget {


using TabWidget = Wt::WTabWidget;
using Toolbar = Wt::WToolBar;
using Button = Wt::WPushButton;
using Break = Wt::WBreak;
using Container = Wt::WContainerWidget;
using Length = Wt::WLength;


static void configureTextEdit(Wt::WTextEdit *textEdit,
                              String const &imageListJs,
                              String const &linkListJs);


Editor::Editor(System const &system, Parent *parent)
  : Widget(system, parent)
  , edits()
  , textEdits()
  , resources()
  , imageListJs(this)
  , linkListJs(this)
  , fileMap()
  , itemChangedSignal()
{
  // File lists mime type
  imageListJs.setMimeType("application/javascript");
  linkListJs.setMimeType("application/javascript");


  // Tab Widget / Text Edits
  auto tabWidget = new TabWidget();
  auto resourceToolbar = new Toolbar();
  auto codesButton = new Button(tr("Codes"));
  auto filesButton = new Button(tr("Files"));
  addWidget(new Break());
  addWidget(new Break());
  addWidget(tabWidget);
  addWidget(new Break());
  addWidget(resourceToolbar);
  resourceToolbar->addButton(codesButton);
  resourceToolbar->addButton(filesButton);

  // Tabs
  auto count = system.languageCount();
  for (decltype(count) i = 0; i < count; ++i) {
    // info
    auto tag = system.languageTag(i);
    auto str = system.languageStr(i);

    // widgets
    auto container = new Container();
    auto edit = new InPlaceEdit();
    auto textEdit = new TextEdit();
    auto toolbar = new Toolbar();
    auto saveButton = new Button(tr("Save"));
    auto uploadButton = new Button(tr("Upload"));
    auto resetButton = new Button(tr("Reset"));
    auto pasteNameButton = new Button(tr("Paste Name"));
    auto pasteContentButton = new Button(tr("Paste Content"));

    // arrangement
    tabWidget->addTab(container, str);
    container->addWidget(new Break());
    container->addWidget(edit);
    container->addWidget(new Break());
    container->addWidget(new Break());
    container->addWidget(textEdit);
    container->addWidget(toolbar);
    toolbar->addButton(saveButton);
    toolbar->addButton(uploadButton);
    toolbar->addButton(resetButton);
    toolbar->addButton(pasteNameButton);
    toolbar->addButton(pasteContentButton);

    // edit
    edit->setPlaceholderText(tr("!!! EMPTY !!!"));

    // text edit
    configureTextEdit(textEdit, Wt::WLink(&imageListJs).url(), Wt::WLink(&linkListJs).url());
    textEdit->setInline(false);
    textEdit->resize(Length::Auto, 600);

    edit->saveButton()->clicked().connect(std::bind(&Editor::saveName, this, tag, edit));
    saveButton->clicked().connect(std::bind(&Editor::saveContent, this, tag, textEdit));
    uploadButton->clicked().connect(std::bind(&Editor::uploadContent, this, tag, textEdit));
    resetButton->clicked().connect(std::bind(&Editor::resetContent, this, tag, textEdit));
    pasteContentButton->clicked().connect(std::bind(&Editor::pasteContent, this, tag, textEdit));
    pasteNameButton->clicked().connect(std::bind(&Editor::pasteName, this, tag, edit));

    edits.push_back(edit);
    textEdits.push_back(textEdit);
  }

  codesButton->clicked().connect(this, &Editor::onCodes);
  filesButton->clicked().connect(this, &Editor::onFiles);
}

Editor::~Editor()
{
}

void Editor::update()
{
  // getting node
  auto node = system().node();
  if (node == nullptr)
    return;

  // regenerate
  // updating file list
  regenerate();

  // setting names and contents
  field::Name name(*node);
  field::Content content(*node);
  auto count = system().languageCount();
  for (decltype(count) i = 0; i < count; ++i) {
    auto tag = system().languageTag(i);
    auto nameStr = name.text(tag);
    auto contentStr = content.text(tag);
    using dnw::utility::string::convert;
    convert(R"rsl(<img .*?src="(\S*?)".*?>)rsl", fileMap, contentStr);
    convert(R"rsl(<a .*?href="(\S*?)".*?>)rsl", fileMap, contentStr);

    edits[i]->setText(nameStr);
    textEdits[i]->setText(contentStr);
  }

}

void Editor::onCodes()
{
  auto node = system().node();
  if (node == nullptr)
    return;

  field::Code code(*node);
  dialog::resource("Codes", code);
}

void Editor::onFiles()
{
  auto node = system().node();
  if (node == nullptr)
    return;

  field::File file(*node);
  dialog::resource("Files", file);
}

enum class ListType {
  Image,
  Link,
};

static void generateFileListJs(ListType listType, dnw::utility::string::Map const &fileMap, String &str)
{
  std::ostringstream stream;

  switch (listType) {
  case ListType::Image:
    stream << "var tinyMCEImageList = new Array(" << std::endl;
    break;
  case ListType::Link:
    stream << "var tinyMCELinkList = new Array(" << std::endl;
    break;
  }

  for (unsigned i = 0; i < fileMap.size(); ++i) {
    auto iter = fileMap.begin();
    std::advance(iter, i);

    if (iter != fileMap.begin())
      stream << "," << std::endl;

    stream << "[\"" << iter->first << "\", \"" << iter->second << "\"]";
  }
  stream << ");" << std::endl;

  str = stream.str();
}

void Editor::regenerate()
{
  // getting node
  auto node = system().node();
  if (node == nullptr)
    return;


  // deleting resources and clearing file map
  for (auto ptr : resources) {
    removeChild(ptr);
    delete ptr;
  }
  resources.clear();
  fileMap.clear();


  // adding resources
  field::File file(*node);
  auto fileCount = file.resourceCount();
  for (decltype(fileCount) i = 0; i < fileCount; ++i) {
    auto name = file.resourceName(i);
    auto path = file.resourcePath(i);
    auto res = new Wt::WFileResource(path, this);

    Wt::WLink link(res);
    fileMap[name] = link.url();
    resources.push_back(res);
  }


  // File lists
  String list;
  generateFileListJs(ListType::Image, fileMap, list);
  imageListJs.setString(list);
  generateFileListJs(ListType::Link, fileMap, list);
  linkListJs.setString(list);
}

Editor::Signal &Editor::itemChanged()
{
  return itemChangedSignal;
}

void Editor::saveName(String const &languageTag, InPlaceEdit *edit)
{
  auto node = system().node();
  if (node == nullptr) {
    dialog::errorMessageBox("Admin", "Cannot be saved!");
    return;
  }

  auto str = edit->text().toUTF8();
  field::Name name(*node);
  name.editText(languageTag, str);

  itemChanged().emit(system().key());
}

void Editor::saveContent(String const &languageTag, TextEdit *textEdit)
{
  auto node = system().node();
  if (node == nullptr) {
    dialog::errorMessageBox("Admin", "Cannot be saved!");
    return;
  }

  // converting
  using dnw::utility::string::convert;
  using Wt::Utils::htmlEncode;

  FileMap map;
  for (auto &item : fileMap) {
    auto filename = item.first;
    auto link = htmlEncode(item.second); // NOTE: There is a hack here. TinyMce returns the image links
                                         // of content htmlEncoded, so you should make the conversion with
                                         // html encoded links.
    map[link] = filename;
  }

  auto str = textEdit->text().toUTF8();
  convert(R"rsl(<img .*?src="(\S*?)".*?>)rsl", map, str);
  convert(R"rsl(<a .*?href="(\S*?)".*?>)rsl", map, str);

  field::Content content(*node);
  content.editText(languageTag, str);

  dialog::messageBox("Admin", "Saved.");
}

void Editor::uploadContent(String const &languageTag, TextEdit *textEdit)
{
  auto node = system().node();
  if (node == nullptr)
    return;

  field::Content content(*node);
  dialog::uploadText(languageTag, content);
  textEdit->setText(content.text(languageTag));
}

void Editor::resetContent(String const &languageTag, TextEdit *textEdit)
{
  auto node = system().node();
  if (node == nullptr)
    return;

  field::Content content(*node);
  textEdit->setText(content.text(languageTag));
}

void Editor::pasteContent(String const &languageTag, TextEdit *textEdit)
{
  Strings tags;
  Strings strs;

  auto count = system().languageCount();
  for (decltype(count) i = 0; i < count; ++i) {
    String tag = system().languageTag(i);
    String str = system().languageStr(i);

    if (languageTag == tag)
      continue;

    tags.push_back(tag);
    strs.push_back(str);
  }

  // if there is not other language.
  if (tags.size() < 1) {
    dialog::errorMessageBox("Admin", "There is no other language!");
    return;
  }

  // if there is only one another language to make copy & paste
  // if there is more than one language there should be an election.
  Index selection = 0;
  if (tags.size() > 1) {
    auto result = dialog::selectWithButtonGroup("Select Language", strs, selection);
    if (result == false)
      return;
  }

  // node
  auto node = system().node();
  if (node == nullptr)
    return;

  // pasting
  field::Content content{*node};
  auto other = content.text(tags[selection]);
  auto text = textEdit->text().toUTF8();

  using dnw::utility::string::convert;
  convert(R"rsl(<img .*?src="(\S*?)".*?>)rsl", fileMap, other);
  convert(R"rsl(<a .*?href="(\S*?)".*?>)rsl", fileMap, other);

  text += other;
  textEdit->setText(text);
}

void Editor::pasteName(String const &languageTag, InPlaceEdit *inPlaceEdit)
{
  Strings tags;
  Strings strs;

  auto count = system().languageCount();
  for (decltype(count) i = 0; i < count; ++i) {
    String tag = system().languageTag(i);
    String str = system().languageStr(i);

    if (languageTag == tag)
      continue;

    tags.push_back(tag);
    strs.push_back(str);
  }

  // if there is not other language.
  if (tags.size() < 1) {
    dialog::errorMessageBox("Admin", "There is no other language!");
    return;
  }

  // if there is only one another language to make copy & paste
  // if there is more than one language there should be an election.
  Index selection = 0;
  if (tags.size() > 1) {
    auto result = dialog::selectWithButtonGroup("Select Language", strs, selection);
    if (result == false)
      return;
  }

  // node
  auto node = system().node();
  if (node == nullptr)
    return;

  // pasting
  field::Name name{*node};
  auto nameStr = name.text(tags[selection]);
  inPlaceEdit->setText(nameStr);
}


static void configureTextEdit(Wt::WTextEdit *textEdit,
                              String const &imageListJs,
                              String const &linkListJs)
{
  textEdit->setExtraPlugins("autolink,lists,spellchecker,pagebreak,style,layer,table,"
                            //"save,advhr,advimage,advlink,emotions,iespell,inlinepopups,"
                            "advhr,advimage,advlink,emotions,iespell,inlinepopups,"
                            "insertdatetime,preview,media,searchreplace,print,contextmenu,"
                            "paste,directionality,fullscreen,noneditable,visualchars,"
                            "nonbreaking,xhtmlxtras,template");

  textEdit->setToolBar(0, //"save,newdocument,|,"
                          "bold,italic,underline,strikethrough,|,"
                          "justifyleft,justifycenter,justifyright,justifyfull,|,"
                          "styleselect,formatselect,fontselect,fontsizeselect");

  textEdit->setToolBar(1, "cut,copy,paste,pastetext,pasteword,|,"
                          "search,replace,|,bullist,numlist,|,"
                          "outdent,indent,blockquote,|,"
                          "undo,redo,|,"
                          "link,unlink,anchor,image,cleanup,help,code,|,"
                          "insertdate,inserttime,preview,|,forecolor,backcolor");

  textEdit->setToolBar(2, "tablecontrols,|,"
                          "hr,removeformat,visualaid,|,"
                          "sub,sup,|,"
                          "charmap,emotions,iespell,media,advhr,|,"
                          "print,|,"
                          "ltr,rtl,|,"
                          "fullscreen");

  textEdit->setToolBar(3, "insertlayer,moveforward,movebackward,absolute,|,"
                          "styleprops,spellchecker,|,"
                          "cite,abbr,acronym,del,ins,attribs,|,"
                          "visualchars,nonbreaking,template,blockquote,pagebreak,|,"
                          "insertfile,insertimage");

  textEdit->setConfigurationSetting("relative_urls", false);
  textEdit->setConfigurationSetting("remove_script_host", false);
  textEdit->setConfigurationSetting("convert_urls", false);
  textEdit->setConfigurationSetting("external_link_list_url", linkListJs);
  textEdit->setConfigurationSetting("external_image_list_url", imageListJs);
}


} // widget
} // dnw

