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
#include "field/name.hpp"
#include "field/content.hpp"
#include "field/file.hpp"
#include "field/code.hpp"
#include "utility/string.hpp"
#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WFileResource>
#include <Wt/WLink>
#include <boost/regex.hpp>
#include "system/node.hpp"


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


} // widget
} // dnw
