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

#include "widget/content.hpp"
#include "system/system.hpp"
#include "system/node.hpp"
#include "field/name.hpp"
#include "field/content.hpp"
#include "field/file.hpp"
#include "field/code.hpp"
#include "utility/string.hpp"
#include <Wt/WText>
#include <Wt/WPushButton>
#include <Wt/WBreak>
#include <Wt/WFileResource>
#include <Wt/WLink>
#include <Wt/WMessageBox>
#include <functional>
#include <boost/regex.hpp>


namespace dnw {
namespace widget {


Content::Content(System const &system, Parent *parent)
  : Widget(system, parent)
  , fileMap()
  , current()
{
}

Content::~Content()
{
}

void Content::update()
{
  createContent();
}

void Content::onShowAll()
{
  createShowAll();
}

void Content::onSearch(Any const &any)
{
  auto str = boost::any_cast<String>(any);

  createSearch(str);
}

Content::Signal &Content::itemChanged()
{
  return itemChangedSignal;
}

void Content::createContent()
{
  // clearing childs
  clear();

  // current node
  auto node = system().node();
  if (node == nullptr)
    return;

  // codes
  field::Code code(*node);
  auto codeCount = code.resourceCount();

  // if ()


  // files
  fileMap.clear();

  field::File file(*node);
  auto fileCount = file.resourceCount();

  for (decltype(fileCount) i = 0; i < fileCount; ++i) {
    auto name = file.resourceName(i);
    auto path = file.resourcePath(i);
    auto res = new Wt::WFileResource(path, this);

    Wt::WLink link(res);

    fileMap[name] = link.url();
  }

  // name
  auto name = field::Name(*node).text(system().language());
  addWidget(new Wt::WText("<h3>" + name + "</h3>"));

  // break
  addWidget(new Wt::WBreak());

  // content
  using dnw::utility::string::convert;

  auto content = field::Content(*node).text(system().language());
  convert(R"rsl(<img .*?src="(\S*?)".*?>)rsl", fileMap, content);
  convert(R"rsl(<a .*?href="(\S*?)".*?>)rsl", fileMap, content);

  auto text = new Wt::WText(content, Wt::XHTMLUnsafeText);
  addWidget(text);
}

void Content::createShowAll()
{


}

void Content::createSearch(String const &str)
{
  // searching
  Anys results;
  search(str, results);

  // checks if there are results
  if (results.empty()) {
    Wt::WMessageBox::show(tr("Find"), tr("No matches found!"), Wt::Ok);
    return;
  }

  // clearing
  clear();

  // generating results
  for (auto &key : results) {
    auto node = system().node(key);
    if (node == nullptr)
      continue;

    field::Name name{*node};
    auto language = system().language();
    auto str = name.text(language);
    auto button = new Wt::WPushButton{str};

    button->clicked().connect(std::bind([this](Any const &key) {
      itemChanged().emit(key);
    }, key));

    addWidget(button);
    addWidget(new Wt::WBreak);
  }
}

void Content::search(String const &str, Anys &results)
{
  results.clear();

  auto root = system().root();
  if (root == nullptr)
    return;

  search(*root, str, results);
}

void Content::search(Node const &node, String const &str, Anys &results)
{
  auto language = system().language();

  field::Name name{node};
  if (name.searchText(language, str, false)) {
    auto key = node.currentKey();
    results.push_back(key);
  }

  auto count = node.nodeCount();
  for (decltype(count) i = 0; i < count; ++i) {
    auto sub = node.node(i);
    if (sub == nullptr)
      continue;

    search(*sub, str, results);
  }
}


} // widget
} // dnw
