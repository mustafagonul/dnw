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
#include "system/device.hpp"
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


namespace dnw {
namespace widget {


Content::Content(Device const &device,
                 String const &language,
                 Any const &key,
                 Parent *parent)
  : Widget(device, language, key, parent)
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

  // current device
  auto clone = device().clone(key());
  if (clone == nullptr)
    return;

  // codes
  field::Code code(*clone);
  auto codeCount = code.codeCount();

  // if ()


  // files
  fileMap.clear();

  field::File file(*clone);
  auto fileCount = file.fileCount();

  for (decltype(fileCount) i = 0; i < fileCount; ++i) {
    auto name = file.fileName(i);
    auto path = file.filePath(i);
    auto res = new Wt::WFileResource(path, this);

    Wt::WLink link(res);

    fileMap[name] = link.url();
  }

  // name
  auto name = field::Name(*clone).name(language());
  new Wt::WText("<h3>" + name + "</h3>", this);

  // break
  new Wt::WBreak(this);

  // content
  auto content = field::Content(*clone).content(language());
  content = convert(content, "<img [[:print:]]*>");
  content = convert(content, "<a href=[[:print:]]*>");

  new Wt::WText(content, Wt::XHTMLUnsafeText, this);
}

String Content::convert(String const &str) const
{
  using dnw::utility::string::replace;

  String result = str;

  for (auto const &file : fileMap) {
    String const &oldFilename = file.first;
    String const &newFilename = file.second;

    replace(oldFilename, newFilename, result);
  }

  return result;
}

String Content::convert(String const &str, String const &expressionStr) const
{
  boost::regex expression(expressionStr);
  boost::match_results<std::string::const_iterator> what;

  auto begin = str.cbegin();
  auto end = str.cend();

  std::string result;
  while (boost::regex_search(begin, end, what, expression))
  {
    std::copy(begin, what[0].first, std::back_inserter(result));
    result += convert(what.str());

    begin = what[0].second;
  }
  std::copy(begin, end, std::back_inserter(result));

  return result;
}


} // widget
} // dnw
