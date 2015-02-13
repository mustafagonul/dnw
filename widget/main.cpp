#include "widget/main.hpp"
#include "widget/tree.hpp"
#include "widget/mode.hpp"
#include "widget/language.hpp"
#include "widget/admin.hpp"
#include "widget/content.hpp"
#include "dialog/password.hpp"
#include "system/system.hpp"
#include <Wt/WApplication>
#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include <Wt/WBreak>


namespace dnw {
namespace widget {


using HBoxLayout = Wt::WHBoxLayout;
using VBoxLayout = Wt::WVBoxLayout;
using Break = Wt::WBreak;


static void setLanguage(String const &language)
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

Main::Main(Parent *parent)
  : config()
  , node()
  , system(config, node)
  , session()
  , rebuildSignal()
  , tree(nullptr)
  , mode(nullptr)
  , language(nullptr)
  , container(nullptr)
  , workspace(nullptr)
{
  // Language
  setMessages();
  setLanguage(system.language());

  // Layouts
  auto mainLayout = new HBoxLayout;
  auto leftLayout = new VBoxLayout;
  auto rightLayout = new VBoxLayout;
  auto topLayout = new HBoxLayout;
  auto bottomLayout = new VBoxLayout;

  // Items
  container = new Container{this};
  tree = new Tree{system, this};
  mode = new Mode{system, this};
  language = new Language{system, this};

  // main
  workspace = new Content{system};
  container->setOverflow(Container::OverflowAuto);
  container->addWidget(workspace);

  // Layout settings
  setLayout(mainLayout);
  mainLayout->addLayout(leftLayout, 1);
  mainLayout->addLayout(rightLayout, 4);
  leftLayout->addWidget(tree);
  rightLayout->addLayout(topLayout);
  rightLayout->addWidget(new Break{this});
  rightLayout->addWidget(new Break{this});
  rightLayout->addWidget(new Break{this});
  rightLayout->addWidget(new Break{this});
  rightLayout->addLayout(bottomLayout, 1, Wt::AlignTop);
  topLayout->addWidget(language, 1, Wt::AlignLeft);
  topLayout->addWidget(mode, 1, Wt::AlignRight);
  bottomLayout->addWidget(container);

  // Connections
  mode->modeChanged().connect(this, &Main::onModeChange);
  language->languageChanged().connect(this, &Main::onLanguageChange);
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
    container->clear();

    workspace = new Content(system);
    container->addWidget(workspace);
    workspace->update();

    return;
  }

  if (mode == "admin") {
    container->clear();

    auto admin = new Admin(system);
    admin->update();
    admin->itemChanged().connect(this, &Main::onItemChange);

    workspace = admin;
    container->addWidget(workspace);

    return;
  }
}
catch (...) {
}

void Main::onLanguageChange(Any const &any)
try
{
  auto lang = boost::any_cast<String>(any);

  system.setLanguage(lang);
  setLanguage(system.language());

  mode->update();
  tree->update();
  workspace->update();
  language->update();
}
catch (...) {
}

void Main::onItemChange(Any const &key)
{
  system.setKey(key);

  tree->update();
  workspace->update();
}


} // widget
} // dnw
