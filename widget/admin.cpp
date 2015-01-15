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

#include "widget/admin.hpp"
#include "system/system.hpp"
#include "system/node.hpp"
#include "field/name.hpp"
#include "field/content.hpp"
#include "field/code.hpp"
#include "field/file.hpp"
#include "dialog/messagebox.hpp"
#include "dialog/resource.hpp"
#include "dialog/text.hpp"
#include "dialog/node.hpp"
#include "dialog/select.hpp"
#include "utility/string.hpp"
#include "wt/stringresource.hpp"
#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include <Wt/WToolBar>
#include <Wt/WPushButton>
#include <Wt/WBreak>
#include <Wt/WTabWidget>
#include <Wt/WTextEdit>
#include <Wt/WCssDecorationStyle>
#include <Wt/WFileResource>
#include <Wt/Utils>
#include <algorithm>


namespace dnw {
namespace widget {


using HBoxLayout = Wt::WHBoxLayout;
using VBoxLayout = Wt::WVBoxLayout;
using Button = Wt::WPushButton;
using Toolbar = Wt::WToolBar;
using TabWidget = Wt::WTabWidget;
using Container = Wt::WContainerWidget;
using Break = Wt::WBreak;
using Length = Wt::WLength;

/*
static void setBorder(Wt::WWidget *widget)
{
  auto style = widget->decorationStyle();

  Wt::WBorder border(Wt::WBorder::Solid);
  style.setBorder(border);

  widget->setDecorationStyle(style);
}
*/

static void configureTextEdit(Wt::WTextEdit *textEdit,
                              String const &imageListJs,
                              String const &linkListJs)
{
  // General options
  /*
  textEdit->setConfigurationSetting("mode", std::string("textareas"));
  textEdit->setConfigurationSetting("theme", std::string("advanced"));
  textEdit->setConfigurationSetting("plugins", std::string("autolink,lists,spellchecker,pagebreak,style,layer,table,"
                                                           "save,advhr,advimage,advlink,emotions,iespell,inlinepopups,"
                                                           "insertdatetime,preview,media,searchreplace,print,contextmenu,"
                                                           "paste,directionality,fullscreen,noneditable,visualchars,"
                                                           "nonbreaking,xhtmlxtras,template"));

  // Theme options
  textEdit->setConfigurationSetting("theme_advanced_buttons1", std::string("save,newdocument,|,"
                                                                           "bold,italic,underline,strikethrough,|,"
                                                                           "justifyleft,justifycenter,justifyright,justifyfull,|,"
                                                                            "styleselect,formatselect,fontselect,fontsizeselect"));

  textEdit->setConfigurationSetting("theme_advanced_buttons2", std::string("cut,copy,paste,pastetext,pasteword,|,"
                                                                           "search,replace,|,bullist,numlist,|,"
                                                                           "outdent,indent,blockquote,|,"
                                                                           "undo,redo,|,"
                                                                           "link,unlink,anchor,image,cleanup,help,code,|,"
                                                                           "insertdate,inserttime,preview,|,forecolor,backcolor"));

  textEdit->setConfigurationSetting("theme_advanced_buttons3", std::string("tablecontrols,|,"
                                                                           "hr,removeformat,visualaid,|,"
                                                                           "sub,sup,|,"
                                                                           "charmap,emotions,iespell,media,advhr,|,"
                                                                           "print,|,"
                                                                           "ltr,rtl,|,"
                                                                           "fullscreen"));

  textEdit->setConfigurationSetting("theme_advanced_buttons4", std::string("insertlayer,moveforward,movebackward,absolute,|,"
                                                                           "styleprops,spellchecker,|,"
                                                                           "cite,abbr,acronym,del,ins,attribs,|,"
                                                                           "visualchars,nonbreaking,template,blockquote,pagebreak,|,"
                                                                           "insertfile,insertimage"));

  textEdit->setConfigurationSetting("theme_advanced_toolbar_location", std::string("top"));
  textEdit->setConfigurationSetting("theme_advanced_toolbar_align", std::string("left"));
  textEdit->setConfigurationSetting("theme_advanced_statusbar_location", std::string("bottom"));
  textEdit->setConfigurationSetting("theme_advanced_resizing", true);

  // Skin options
  textEdit->setConfigurationSetting("skin", std::string("o2k7"));
  textEdit->setConfigurationSetting("skin_variant", std::string("silver"));


  // Drop lists for link/image/media/template dialogs
  textEdit->setConfigurationSetting("template_external_list_url", std::string("js/template_list.js"));
  textEdit->setConfigurationSetting("external_link_list_url", std::string("js/link_list.js"));
  textEdit->setConfigurationSetting("external_image_list_url", std::string("js/image_list.js"));
  textEdit->setConfigurationSetting("media_external_list_url", std::string("js/media_list.js"));
  */

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

Admin::Admin(System const &system, Parent *parent)
  : Widget(system, parent)
  , edits()
  , textEdits()
  , resources()
  , imageListJs(this)
  , linkListJs(this)
  , fileMap()
  , rebuildSignal()
{
  /*
  // layout
  auto mainLayout = new VBoxLayout();
  auto topLayout = new HBoxLayout();
  auto bottomLayout = new VBoxLayout();
  setLayout(mainLayout);
  mainLayout->addLayout(topLayout);
  mainLayout->addLayout(bottomLayout);
  */

	// File lists mime type
  imageListJs.setMimeType("application/javascript");
  linkListJs.setMimeType("application/javascript");


  // Node commands
  auto nodeToolbar = new Toolbar(this);
  auto addNodeButton = new Button(tr("Add Node"));
  auto removeNodeButton = new Button(tr("Remove Node"));
  auto moveNodeUpButton = new Button(tr("Move Node Up"));
  auto moveNodeDownButton = new Button(tr("Move Node Down"));
  addWidget(nodeToolbar);
  nodeToolbar->addButton(addNodeButton);
  nodeToolbar->addButton(removeNodeButton);
  nodeToolbar->addButton(moveNodeUpButton);
  nodeToolbar->addButton(moveNodeDownButton);

  // File commands
  auto fileToolbar = new Toolbar(this);
  auto addFileButton = new Button(tr("Add File"));
  auto removeFileButton = new Button(tr("Remove File"));
  auto moveFileButton = new Button(tr("Move File"));
  addWidget(fileToolbar);
  fileToolbar->addButton(addFileButton);
  fileToolbar->addButton(removeFileButton);
  fileToolbar->addButton(moveFileButton);

  // Code commands
  auto codeToolbar = new Toolbar(this);
  auto addCodeButton = new Button(tr("Add Code"));
  auto removeCodeButton = new Button(tr("Remove Code"));
  auto moveCodeButton = new Button(tr("Move Code"));
  addWidget(codeToolbar);
  codeToolbar->addButton(addCodeButton);
  codeToolbar->addButton(removeCodeButton);
  codeToolbar->addButton(moveCodeButton);

  // Config commands
  auto configToolbar = new Toolbar{this};
  auto nodeConfigButton = new Button{tr("Node Config")};
  auto globalConfigButton = new Button{tr("Global Config")};
  auto rebuildButton = new Button{tr("Rebuild")};
  addWidget(configToolbar);
  configToolbar->addButton(nodeConfigButton);
  configToolbar->addButton(globalConfigButton);
  configToolbar->addButton(rebuildButton);

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
    auto pasteButton = new Button(tr("Paste"));

    // arrangement
    tabWidget->addTab(container, str);
    container->addWidget(edit);
    container->addWidget(new Break());
    container->addWidget(new Break());
    container->addWidget(textEdit);
    container->addWidget(toolbar);
    toolbar->addButton(saveButton);
    toolbar->addButton(uploadButton);
    toolbar->addButton(resetButton);
    toolbar->addButton(pasteButton);

    // edit
    edit->setPlaceholderText(tr("!!! EMPTY !!!"));

    // text edit
    configureTextEdit(textEdit, Wt::WLink(&imageListJs).url(), Wt::WLink(&linkListJs).url());
    textEdit->setInline(false);
    textEdit->resize(Length::Auto, 600);

    edit->saveButton()->clicked().connect(std::bind(&Admin::saveName, this, tag, edit));
    saveButton->clicked().connect(std::bind(&Admin::saveContent, this, tag, textEdit));
    uploadButton->clicked().connect(std::bind(&Admin::uploadContent, this, tag, textEdit));
    resetButton->clicked().connect(std::bind(&Admin::resetContent, this, tag, textEdit));
    pasteButton->clicked().connect(std::bind(&Admin::pasteContent, this, tag, textEdit));

    edits.push_back(edit);
    textEdits.push_back(textEdit);
  }

  // connections
  addNodeButton->clicked().connect(this, &Admin::addNode);
  removeNodeButton->clicked().connect(this, &Admin::removeNode);
  moveNodeUpButton->clicked().connect(this, &Admin::moveNodeUp);
  moveNodeDownButton->clicked().connect(this, &Admin::moveNodeDown);

  addFileButton->clicked().connect(this, &Admin::addFile);
  removeFileButton->clicked().connect(this, &Admin::removeFile);
  moveFileButton->clicked().connect(this, &Admin::moveFile);

  addCodeButton->clicked().connect(this, &Admin::addCode);
  removeCodeButton->clicked().connect(this, &Admin::removeCode);
  moveCodeButton->clicked().connect(this, &Admin::moveCode);

  codesButton->clicked().connect(this, &Admin::onCodes);
  filesButton->clicked().connect(this, &Admin::onFiles);

  nodeConfigButton->clicked().connect(this, &Admin::nodeConfig);
  globalConfigButton->clicked().connect(this, &Admin::globalConfig);
  rebuildButton->clicked().connect(this, &Admin::rebuildConfig);
}

Admin::~Admin()
{
}

void Admin::update()
{
  // getting node
  auto node = system().node();
  if (node == nullptr)
    return;

  // updating file list
  updateFileList();

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

void Admin::onCodes()
{
  auto node = system().node();
  if (node == nullptr)
    return;

  field::Code code(*node);
  dialog::resource("Codes", code);
}

void Admin::onFiles()
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

void Admin::updateFileList()
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


void Admin::saveName(String const &languageTag, InPlaceEdit *edit)
{
  auto node = system().node();
  if (node == nullptr) {
    dialog::errorMessageBox("Admin", "Cannot be saved!");
    return;
  }

  auto str = edit->text().toUTF8();
  field::Name name(*node);
  name.editText(languageTag, str);

  changed().emit(system().key());
}

void Admin::saveContent(String const &languageTag, TextEdit *textEdit)
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

void Admin::uploadContent(String const &languageTag, TextEdit *textEdit)
{
  auto node = system().node();
  if (node == nullptr)
    return;

  field::Content content(*node);
  dialog::uploadText(languageTag, content);
  textEdit->setText(content.text(languageTag));
}

void Admin::resetContent(String const &languageTag, TextEdit *textEdit)
{
  auto node = system().node();
  if (node == nullptr)
    return;

  field::Content content(*node);
  textEdit->setText(content.text(languageTag));
}

void Admin::pasteContent(String const &languageTag, TextEdit *textEdit)
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
    auto result = dialog::select("Select Language", strs, selection);
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
  text += other;
  textEdit->setText(text);
}

void Admin::addNode()
{
  auto node = system().node();

  if (node == nullptr) {
    dialog::errorMessageBox("Admin", "Cannot be added!");
    return;
  }

  if (node->pushNode() == false) {
    dialog::errorMessageBox("Admin", "Cannot be added!");
    return;
  }

  auto last = node->last();
  if (last == nullptr) {
    dialog::errorMessageBox("Admin", "Cannot be added!");
    return;
  }

  auto k = last->currentKey();
  changed().emit(k);

  dialog::messageBox("Admin", "Added.");
}

void Admin::removeNode()
{
  auto node = system().node();
  if (node == nullptr) {
    dialog::errorMessageBox("Admin", "Cannot be removed!");
    return;
  }

  auto result = dialog::removeNode(*node, system().language());
  if (result) {
    changed().emit(system().key());
    dialog::messageBox("Admin", "Removed.");
  }
}

void Admin::moveNodeUp()
{
  auto node = system().node();
  if (node == nullptr) {
    dialog::errorMessageBox("Admin", "Cannot be moved!");
    return;
  }

  auto result = dialog::moveNodeUp(*node, system().language());
  if (result) {
    changed().emit(system().key());
    dialog::messageBox("Admin", "Moved.");
  }
}

void Admin::moveNodeDown()
{
  auto node = system().node();
  if (node == nullptr) {
    dialog::errorMessageBox("Admin", "Cannot be moved!");
    return;
  }

  auto result = dialog::moveNodeDown(*node, system().language());
  if (result) {
    changed().emit(system().key());
    dialog::messageBox("Admin", "Moved.");
  }
}

void Admin::addFile()
{
  auto node = system().node();
  if (node == nullptr) {
    dialog::errorMessageBox("Add File");
    return;
  }

  field::File file(*node);
  dialog::addResource("Add File", file);

  updateFileList();
}

void Admin::removeFile()
{
  auto node = system().node();
  if (node == nullptr) {
    dialog::errorMessageBox("Remove File");
    return;
  }

  field::File file(*node);
  dialog::removeResource("Remove File", file);

  updateFileList();
}

void Admin::moveFile()
{
  // TODO mustafa:
}

void Admin::addCode()
{
  auto node = system().node();
  if (node == nullptr) {
    dialog::errorMessageBox("Add Code");
    return;
  }

  field::Code code(*node);
  dialog::addResource("Add Code", code);
}

void Admin::removeCode()
{
  auto node = system().node();
  if (node == nullptr) {
    dialog::errorMessageBox("Remove Code");
    return;
  }

  field::Code code(*node);
  dialog::removeResource("Remove Code", code);
}

void Admin::moveCode()
{
  // TODO mustafa:
}

void Admin::nodeConfig()
{

}

void Admin::globalConfig()
{

}

void Admin::rebuildConfig()
{
  rebuildSignal.emit();
}


} // widget
} // dnw
