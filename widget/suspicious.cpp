#include "widget/suspicious.hpp"
#include "system/system.hpp"
#include "system/node.hpp"
#include "field/name.hpp"
#include "field/content.hpp"
#include <Wt/WPushButton>
#include <Wt/WBreak>


namespace dnw {
namespace widget {


using Node = dnw::system::Node;
using Results = std::vector<Result>;
using Button = Wt::WPushButton;
using Break = Wt::WBreak;


static void check(Node const &node, String const &baseLanguage, String const &language, Results &results);
static Result checkName(Node const &node, String const &baseLanguage, String const &language);
static Result checkContent(Node const &node, String const &baseLanguage, String const &language);


Suspicious::Suspicious(System const &system, Parent *parent)
  : Widget(system, parent)
  , itemChangedSignal()
{
}

Suspicious::~Suspicious()
{
}

void Suspicious::update()
{
  clear();

  // space
  new Break{this};
  new Break{this};

  // root
  auto root = system().root();
  if (root == nullptr)
    return;

  Results results;

  // base language
  auto baseLanguage = system().baseLanguage();
  auto count = system().languageCount();
  for (decltype(count) i = 0; i < count; ++i) {
    auto language = system().languageTag(i);
    check(*root, baseLanguage, language, results);
  }

  for (auto &result : results) {
    auto message = result.all("\n");
    if (message.empty())
      continue;

    auto key = result.key();
    auto button = new Button{this};
    auto function = [this](Any const &key) { itemChanged().emit(key); };
    button->clicked().connect(std::bind(function, key));
    button->setText(message);

    new Break{this};
  }
}

Suspicious::Signal &Suspicious::itemChanged()
{
  return itemChangedSignal;
}

static void check(Node const &node, String const &baseLanguage, String const &language, Results &results)
{
  // node result
  auto key = node.currentKey();
  Result result(key);
  result += checkName(node, baseLanguage, language);
  result += checkContent(node, baseLanguage, language);
  results.push_back(result);

  // child nodes
  auto count = node.nodeCount();
  for (decltype(count) i = 0; i < count; ++i) {
    auto sub = node.node(i);
    if (sub == nullptr)
      continue;

    check(*sub, baseLanguage, language, results);
  }
}

static Result checkName(Node const &node, String const &baseLanguage, String const &language)
{
  Result result;

  // name check
  field::Name name(node);
  auto nameStr = name.text(language);
  if (nameStr.empty()) {
    String message = language + " No Name!";
    result.add(message);
  }

  // if the language is base language there is nothing to check
  // everything is allright
  if (baseLanguage == language)
    return result;

  // if baseTime greater than time, base is changed and current is suspicious.
  auto time = name.lastModification(language);
  auto baseTime = name.lastModification(baseLanguage);
  if (baseTime >= time) { // we are checking also they are equal!
    String message = language + " Old Name!";
    result.add(message);
  }

  return result;
}

static Result checkContent(Node const &node, String const &baseLanguage, String const &language)
{
  Result result;

  // content check
  field::Content content(node);
  auto contentStr = content.text(language);
  if (contentStr.empty()) {
    String message = language + " No Content!";
    result.add(message);
  }

  // if the language is base language there is nothing to check
  // everything is allright
  if (baseLanguage == language)
    return result;

  // if baseTime greater than time, base is changed and current is suspicious.
  auto time = content.lastModification(language);
  auto baseTime = content.lastModification(baseLanguage);
  if (baseTime >= time) { // we are checking also they are equal!
    String message = language + " Old Content!";
    result.add(message);
  }

  return result;
}


} // widget
} // dnw

