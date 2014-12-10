/*
 * Copyright (C) 2014 Mustafa G??n??l
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
#include "system/device.hpp"
#include "field/name.hpp"
#include "field/content.hpp"
#include "field/code.hpp"
#include "field/file.hpp"
#include "dialog/messagebox.hpp"
#include "dialog/resource.hpp"
#include "dialog/node.hpp"
#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include <Wt/WPushButton>
#include <Wt/WLabel>
#include <Wt/WTextEdit>


#define EMPTY_NAME ("!!!! EMPTY !!!!")


namespace dnw {
namespace widget {


using HBoxLayout = Wt::WHBoxLayout;
using VBoxLayout = Wt::WVBoxLayout;
using Button = Wt::WPushButton;
using Label = Wt::WLabel;
using Container = Wt::WContainerWidget;
using Length = Wt::WLength;


static void configureTextEdit(Wt::WTextEdit *textEdit)
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
}

Admin::Admin(Device const &device,
             String const &language,
             Any const &key,
             Parent *parent)
  : Widget(device, language, key, parent)
  , leftEdit(nullptr)
  , rightEdit(nullptr)
  , leftTextEdit(nullptr)
  , rightTextEdit(nullptr)
{
  // layout
  auto mainLayout = new VBoxLayout();
  auto topLayout = new HBoxLayout();
  auto bottomLayout = new HBoxLayout();
  auto bottomLeftLayout = new VBoxLayout();
  auto bottomRightLayout = new VBoxLayout();
  setLayout(mainLayout);
  mainLayout->addLayout(topLayout);
  mainLayout->addLayout(bottomLayout);
  bottomLayout->addLayout(bottomLeftLayout);
  bottomLayout->addLayout(bottomRightLayout);


  // Node commands
  auto addNodeButton = new Button("Add Node", this);
  auto removeNodeButton = new Button("Remove Node", this);
  auto moveNodeUpButton = new Button("Move Node Up", this);
  auto moveNodeDownButton = new Button("Move Node Down", this);

  // File commands
  auto addFileButton = new Button("Add File", this);
  auto removeFileButton = new Button("Remove File", this);
  auto moveFileButton = new Button("Move File", this);

  // Code commands
  auto addCodeButton = new Button("Add Code", this);
  auto removeCodeButton = new Button("Remove Code", this);
  auto moveCodeButton = new Button("Move Code", this);

  topLayout->addWidget(addNodeButton);
  topLayout->addWidget(removeNodeButton);
  topLayout->addWidget(moveNodeUpButton);
  topLayout->addWidget(moveNodeDownButton);
  topLayout->addWidget(addFileButton);
  topLayout->addWidget(removeFileButton);
  topLayout->addWidget(moveFileButton);
  topLayout->addWidget(addCodeButton);
  topLayout->addWidget(removeCodeButton);
  topLayout->addWidget(moveCodeButton);


  // Containers & labels & push
  auto leftLabel = new Label("Engish", this);
  auto rightLabel = new Label("Turkish", this);
  auto leftEditContainer = new Container(this);
  auto rightEditContainer = new Container(this);
  auto leftTextEditContainer = new Container(this);
  auto rightTextEditContainer = new Container(this);
  auto leftButton = new Button("Save", this);
  auto rightButton = new Button("Save", this);
  auto codesButton = new Button("Codes", this);
  auto filesButton = new Button("Files", this);

  // Edits
  leftEdit = new InPlaceEdit("Empty", leftEditContainer);
  rightEdit = new InPlaceEdit("Empty", rightEditContainer);
  leftTextEdit = new TextEdit(leftTextEditContainer);
  rightTextEdit = new TextEdit(rightTextEditContainer);
  configureTextEdit(leftTextEdit);
  configureTextEdit(rightTextEdit);
  leftTextEdit->setInline(false);
  leftTextEdit->setInline(false);
  leftTextEdit->resize(Length::Auto, 600);
  rightTextEdit->resize(Length::Auto, 600);

  bottomLeftLayout->addWidget(leftLabel);
  bottomLeftLayout->addWidget(leftEditContainer);
  bottomLeftLayout->addWidget(leftTextEditContainer);
  bottomLeftLayout->addWidget(leftButton);
  bottomRightLayout->addWidget(rightLabel);
  bottomRightLayout->addWidget(rightEditContainer);
  bottomRightLayout->addWidget(rightTextEditContainer);
  bottomRightLayout->addWidget(rightButton);
  mainLayout->addWidget(filesButton);
  mainLayout->addWidget(codesButton);


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


  leftEdit->saveButton()->clicked().connect(this, &Admin::saveLeftName);
  rightEdit->saveButton()->clicked().connect(this, &Admin::saveRightName);
  leftButton->clicked().connect(this, &Admin::saveLeftContent);
  rightButton->clicked().connect(this, &Admin::saveRightContent);

  codesButton->clicked().connect(this, &Admin::onCodes);
  filesButton->clicked().connect(this, &Admin::onFiles);


  // TODO mustafa:
  /*
  leftTextEdit->keyPressed().connect(std::bind([]{

  }));
  */
}

Admin::~Admin()
{
}

void Admin::update()
{
  auto clone = device().clone(key());
  if (clone == nullptr)
    return;

  field::Name name(*clone);
  field::Content content(*clone);

  auto leftName = name.name("en");
  if (leftName.empty())
    leftName = EMPTY_NAME;
  auto rightName = name.name("tr");
  if (rightName.empty())
    rightName = EMPTY_NAME;


  leftEdit->setText(leftName);
  rightEdit->setText(rightName);
  leftTextEdit->setText(content.content("en"));
  rightTextEdit->setText(content.content("tr"));
}

void Admin::onCodes()
{
  auto clone = device().clone(key());
  if (clone == nullptr)
    return;

  field::Code code(*clone);
  dialog::resource("Codes", code);
}

void Admin::onFiles()
{
  auto clone = device().clone(key());
  if (clone == nullptr)
    return;

  field::File file(*clone);
  dialog::resource("Files", file);
}

void Admin::saveLeftName()
{
  auto clone = device().clone(key());
  if (clone == nullptr) {
    dialog::errorMessageBox("Admin", "Cannot be saved!");
    return;
  }


  auto str = leftEdit->text().toUTF8();
  if (str == EMPTY_NAME)
    str = "";

  field::Name name(*clone);
  name.editName("en", str);


  changed().emit();
}

void Admin::saveRightName()
{
  auto clone = device().clone(key());
  if (clone == nullptr) {
    dialog::errorMessageBox("Admin", "Cannot be saved!");
    return;
  }

  auto str = rightEdit->text().toUTF8();
  if (str == EMPTY_NAME)
    str = "";

  field::Name name(*clone);
  name.editName("tr", str);


  changed().emit();
}

void Admin::saveLeftContent()
{
  auto clone = device().clone(key());
  if (clone == nullptr) {
    dialog::errorMessageBox("Admin", "Cannot be saved!");
    return;
  }

  auto str = leftTextEdit->text().toUTF8();

  field::Content content(*clone);
  content.editContent("en", str);

  dialog::messageBox("Admin", "Saved.");
}

void Admin::saveRightContent()
{
  auto clone = device().clone(key());
  if (clone == nullptr) {
    dialog::errorMessageBox("Admin", "Cannot be saved!");
    return;
  }

  auto str = rightTextEdit->text().toUTF8();

  field::Content content(*clone);
  content.editContent("tr", str);

  dialog::messageBox("Admin", "Saved.");
}

void Admin::addNode()
{
  auto clone = device().clone(key());

  if (clone == nullptr) {
    dialog::errorMessageBox("Admin", "Cannot be added!");
    return;
  }

  if (clone->pushNode() == false) {
    dialog::errorMessageBox("Admin", "Cannot be added!");
    return;
  }

  auto last = clone->lastDevice();
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
  auto clone = device().clone(key());
  if (clone == nullptr) {
    dialog::errorMessageBox("Admin", "Cannot be removed!");
    return;
  }

  auto result = dialog::removeNode(*clone, language());
  if (result) {
    changed().emit(key());
    dialog::messageBox("Admin", "Removed.");
  }
}

void Admin::moveNodeUp()
{
  auto clone = device().clone(key());
  if (clone == nullptr) {
    dialog::errorMessageBox("Admin", "Cannot be moved!");
    return;
  }

  auto result = dialog::moveNodeUp(*clone, language());
  if (result) {
    changed().emit(key());
    dialog::messageBox("Admin", "Moved");
  }
}

void Admin::moveNodeDown()
{
  auto clone = device().clone(key());
  if (clone == nullptr) {
    dialog::errorMessageBox("Admin", "Cannot be moved!");
    return;
  }

  auto result = dialog::moveNodeDown(*clone, language());
  if (result) {
    changed().emit(key());
    dialog::messageBox("Admin", "Moved");
  }
}

void Admin::addFile()
{
  auto clone = device().clone(key());
  if (clone == nullptr) {
    dialog::errorMessageBox("Add File");
    return;
  }

  field::File file(*clone);
  dialog::addResource("Add File", file);
}

void Admin::removeFile()
{
  auto clone = device().clone(key());
  if (clone == nullptr) {
    dialog::errorMessageBox("Remove File");
    return;
  }

  field::File file(*clone);
  dialog::removeResource("Remove File", file);
}

void Admin::moveFile()
{
  // TODO mustafa:
}

void Admin::addCode()
{
  auto clone = device().clone(key());
  if (clone == nullptr) {
    dialog::errorMessageBox("Add Code");
    return;
  }

  field::Code code(*clone);
  dialog::addResource("Add Code", code);
}

void Admin::removeCode()
{
  auto clone = device().clone(key());
  if (clone == nullptr) {
    dialog::errorMessageBox("Remove Code");
    return;
  }

  field::Code code(*clone);
  dialog::removeResource("Remove Code", code);
}

void Admin::moveCode()
{
  // TODO mustafa:
}


} // widget
} // dnw
