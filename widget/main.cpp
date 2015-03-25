#include "widget/main.hpp"
#include "widget/navigationbar.hpp"
#include "widget/tree.hpp"
#include "widget/admin.hpp"
#include "widget/content.hpp"
#include "dialog/password.hpp"
#include "system/system.hpp"
#include <Wt/WApplication>
#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>


namespace dnw {
namespace widget {


using HBoxLayout = Wt::WHBoxLayout;
using VBoxLayout = Wt::WVBoxLayout;


static void setLocale(String const &language)
{
  auto app = Wt::WApplication::instance();
  if (app == nullptr)
    return;

  app->setLocale(language);
}

static void setMessages()
{
  auto app = Wt::WApplication::instance();
  if (app == nullptr)
    return;

  app->messageResourceBundle().use("messages/general");
}

Main::Main(System &system_, Session &session_, Parent *parent)
  : system(system_)
  , session(session_)
  , navigationBar(nullptr)
  , tree(nullptr)
  , workspaceContainer(nullptr)
  , workspace(nullptr)
{
  // Language
  setMessages();
  setLocale(system.language());

  // Layout
  auto main = new HBoxLayout;
  auto right = new Container{this};
  auto left = new Container{this};

  // Items
  tree = new Tree{system, this};
  navigationBar = new NavigationBar{system, this};
  workspaceContainer = new Container{this};

  // Main
  workspace = new Content{system};
  workspaceContainer->setOverflow(Container::OverflowAuto);
  workspaceContainer->addWidget(workspace);

  // Layout settings
  setLayout(main);
  main->addWidget(right, 10);
  main->addStretch(1);
  main->addWidget(left, 40);
  right->addWidget(tree);
  left->addWidget(navigationBar);
  left->addWidget(workspaceContainer);

  // Connections
  navigationBar->modeChanged().connect(this, &Main::onModeChange);
  navigationBar->languageChanged().connect(this, &Main::onLanguageChange);
  tree->itemChanged().connect(this, &Main::onItemChange);

  // Main update
  workspace->update();
}

Main::~Main()
{
}

void Main::onModeChange(Any const &any)
try
{
  auto mode = boost::any_cast<String>(any);

  if (dialog::checkPassword() == false)
    mode = "guest";

  if (mode == "admin" && dialog::password(session) == false)
    mode = "guest";

  if (mode == "guest") {
    workspaceContainer->clear();

    workspace = new Content(system);
    workspaceContainer->addWidget(workspace);
    workspace->update();

    return;
  }

  if (mode == "admin") {
    workspaceContainer->clear();

    auto admin = new Admin(system);
    admin->update();
    admin->itemChanged().connect(this, &Main::onItemChange);

    workspace = admin;
    workspaceContainer->addWidget(workspace);

    return;
  }
}
catch (...) {
}

void Main::onLanguageChange(Any const &any)
try
{
  // changes system language
  auto lang = boost::any_cast<String>(any);
  system.setLanguage(lang);

  // changes locale language
  setLocale(system.language()); // TODO mustafa: give a more proper name to this function

  navigationBar->update();
  tree->update();
  workspace->update();
}
catch (...) {
}

void Main::onItemChange(Any const &key)
{
  system.setKey(key);

  navigationBar->update();
  tree->update();
  workspace->update();
}


} // widget
} // dnw
