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
#include "widget/editor.hpp"
#include "widget/suspicious.hpp"
#include "system/system.hpp"
#include "system/node.hpp"
#include "field/code.hpp"
#include "field/file.hpp"
#include "dialog/messagebox.hpp"
#include "dialog/node.hpp"
#include "dialog/resource.hpp"
#include "wt/stringresource.hpp"
#include <Wt/WToolBar>
#include <Wt/WPushButton>
#include <Wt/WTextEdit>


#include <algorithm>


namespace dnw {
namespace widget {


using Toolbar = Wt::WToolBar;
using Button = Wt::WPushButton;



Admin::Admin(System const &system, Parent *parent)
  : Decorator(system, parent)
  , itemChangedSignal()
{
  // Node commands
  auto nodeToolbar = new Toolbar{this};
  auto addNodeButton = new Button{tr("Add Node")};
  auto removeNodeButton = new Button{tr("Remove Node")};
  auto moveNodeUpButton = new Button{tr("Move Node Up")};
  auto moveNodeDownButton = new Button{tr("Move Node Down")};
  addWidget(nodeToolbar);
  nodeToolbar->addButton(addNodeButton);
  nodeToolbar->addButton(removeNodeButton);
  nodeToolbar->addButton(moveNodeUpButton);
  nodeToolbar->addButton(moveNodeDownButton);

  // File commands
  auto fileToolbar = new Toolbar{this};
  auto addFileButton = new Button{tr("Add File")};
  auto removeFileButton = new Button{tr("Remove File")};
  auto moveFileButton = new Button{tr("Move File")};
  addWidget(fileToolbar);
  fileToolbar->addButton(addFileButton);
  fileToolbar->addButton(removeFileButton);
  fileToolbar->addButton(moveFileButton);

  // Code commands
  auto codeToolbar = new Toolbar{this};
  auto addCodeButton = new Button{tr("Add Code")};
  auto removeCodeButton = new Button{tr("Remove Code")};
  auto moveCodeButton = new Button{tr("Move Code")};
  addWidget(codeToolbar);
  codeToolbar->addButton(addCodeButton);
  codeToolbar->addButton(removeCodeButton);
  codeToolbar->addButton(moveCodeButton);

  // Config commands
  auto configToolbar = new Toolbar{this};
  auto nodeConfigButton = new Button{tr("Node Config")};
  auto globalConfigButton = new Button{tr("Global Config")};
  addWidget(configToolbar);
  configToolbar->addButton(nodeConfigButton);
  configToolbar->addButton(globalConfigButton);

  // View commands
  auto viewToolbar = new Toolbar{this};
  auto editorButton = new Button{tr("Editor")};
  auto suspiciousButton = new Button{tr("Suspicious")};
  addWidget(viewToolbar);
  viewToolbar->addButton(editorButton);
  viewToolbar->addButton(suspiciousButton);

  // Decorator
  addContainer();

  // connections
  // node
  addNodeButton->clicked().connect(this, &Admin::addNode);
  removeNodeButton->clicked().connect(this, &Admin::removeNode);
  moveNodeUpButton->clicked().connect(this, &Admin::moveNodeUp);
  moveNodeDownButton->clicked().connect(this, &Admin::moveNodeDown);

  // file
  addFileButton->clicked().connect(this, &Admin::addFile);
  removeFileButton->clicked().connect(this, &Admin::removeFile);
  moveFileButton->clicked().connect(this, &Admin::moveFile);

  // code
  addCodeButton->clicked().connect(this, &Admin::addCode);
  removeCodeButton->clicked().connect(this, &Admin::removeCode);
  moveCodeButton->clicked().connect(this, &Admin::moveCode);

  // config
  nodeConfigButton->clicked().connect(this, &Admin::nodeConfig);
  globalConfigButton->clicked().connect(this, &Admin::globalConfig);

  // view
  editorButton->clicked().connect(this, &Admin::editor);
  suspiciousButton->clicked().connect(this, &Admin::suspicious);
}

Admin::~Admin()
{
}

void Admin::update()
{
  editor();

  Decorator::update();
}

void Admin::regenerate()
{
  Decorator::regenerate();
}

Admin::Signal &Admin::itemChanged()
{
  return itemChangedSignal;
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
  itemChanged().emit(k);

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
    itemChanged().emit(system().key());
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
    itemChanged().emit(system().key());
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
    itemChanged().emit(system().key());
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

  regenerate();
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

  regenerate();
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

void Admin::editor()
{
  auto editor = new Editor{system()};

  setWidget(editor);

  auto emitter = [this](Any const &any) { itemChanged().emit(any); };

  editor->itemChanged().connect(std::bind(emitter, std::placeholders::_1));
}

void Admin::suspicious()
{
  auto suspicious = new Suspicious{system()};

  setWidget(suspicious);

  auto emitter = [this](Any const &any) { itemChanged().emit(any); };

  suspicious->itemChanged().connect(std::bind(emitter, std::placeholders::_1));
}

} // widget
} // dnw
