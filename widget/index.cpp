#include "widget/index.hpp"
#include "system/system.hpp"
#include "system/node.hpp"
#include "field/name.hpp"
#include <Wt/WPushButton>
#include <Wt/WBreak>


namespace dnw {
namespace widget {


Index::Index(System const &system, Parent *parent)
  : Widget(system, parent)
{
}

Index::~Index()
{
}

void Index::update()
{
  // clearing
  clear();

  // traverse function
  using Node = dnw::system::Node;
  using NodeInfoMap = std::map<String, String>;
  using GetInfo = std::function<void (Node const &, String const &, NodeInfoMap &)>;

  GetInfo getInfo = [&getInfo](system::Node const &node, String const &language, NodeInfoMap &map) {
    field::Name name(node);
    auto nameStr = name.text(language);
    auto linkStr = boost::any_cast<String>(node.currentKey());
    map[linkStr] = nameStr;

    auto count = node.nodeCount();
    for (decltype(count) i = 0; i < count; ++i) {
      auto sub = node.node(i);
      if (sub == nullptr)
        continue;

      getInfo(*sub, language, map);
    }
  };

  // getting info
  auto count = system().languageCount();
  auto root = system().root();
  if (root == nullptr)
    return;

  // traversing
  for (decltype(count) i = 0; i < count; ++i) {
    auto language = system().languageTag(i);
    NodeInfoMap map;
    getInfo(*root, language, map);

    for (auto &item : map) {
      auto button = new Wt::WPushButton;
      auto path = "/" + language + "/" + item.first;
      Wt::WLink link(Wt::WLink::InternalPath, path);
      button->setText(item.second);
      button->setLink(link);

      addWidget(button);
      addWidget(new Wt::WBreak);
    }
  }
}


} // widget
} // dnw
