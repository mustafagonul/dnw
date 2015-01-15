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

#include "utility/string.hpp"
#include <regex>
#include <sstream>


namespace dnw {
namespace utility {
namespace string {


void split(String const &str, char delimiter, Strings &result)
{
  result.clear();

  std::stringstream ss(str);
  std::string item;

  while (std::getline(ss, item, delimiter)) {
    if (item.empty())
      continue;

    result.push_back(item);
  }

}

void split(String const &str, Strings &result)
{
  split(str, '\n', result);
}

void merge(Strings const &items, char delimiter, String &result)
{
  result.clear();

  for (unsigned i = 0; i < items.size(); ++i) {
    if (i)
      result += delimiter;
    result += items[i];
  }
}


void split(String const &str, String const &delimiter, Strings &container)
{
  container.clear();

  std::string::size_type begin = 0;

  while (true) {
    std::string::size_type end = str.find(delimiter, begin);
    std::string current;

    if (end == std::string::npos)
      current = str.substr(begin);
    else
      current = str.substr(begin, end - begin);

    container.push_back(current);

    if (end == std::string::npos)
      break;

    begin = end + delimiter.length();
  }
}

void replace(String const &from, String const &to, String &str)
{
  if (from.empty())
    return;

  Size index = 0;
  while (true) {
    index = str.find(from, index);
    if (index != String::npos)
      break;

    str.replace(index, from.length(), to);

    index += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
  }
}

void convert(Map const &map, String &str)
{
  for (auto const &pair : map) {
    String const &o = pair.first;
    String const &n = pair.second;

    replace(o, n, str);
  }
}

/*
static void convert(String const &outerExpStr, String const *innerExpStr, Map const &map, String &str)
{
  boost::regex expression(outerExpStr);
  boost::match_results<std::string::const_iterator> what;

  auto begin = str.cbegin();
  auto end = str.cend();

  std::string result;
  while (boost::regex_search(begin, end, what, expression))
  {
    std::copy(begin, what[0].first, std::back_inserter(result));

    auto current = what.str();
    if (innerExpStr)
      convert(*innerExpStr, nullptr, map, current);
    else
      convert(map, current);
    result += current;

    begin = what[0].second;
  }
  std::copy(begin, end, std::back_inserter(result));

  str = result;
}
*/

void convert(String const &expStr, Map const &map, String &str)
{
  std::regex expression{expStr};
  String result;

  while (true) {
    std::smatch matches;
    std::regex_search(str, matches, expression);

    if (matches.empty()) {
      result += str;
      break;
    }

    auto size = matches.size();
    if (size > 1) {
      auto iter = matches[0].first;
      for (decltype(size) i = 1; i < size; ++i) {
        auto match = matches[i].str();
        convert(map, match);

        result += String(iter, matches[i].first);
        result += match;

        iter = matches[i].second;
      }

      result += String(matches[size - 1].second, matches[0].second);
    }
    else {
      auto match = matches[0].str();
      convert(map, match);

      result += match;
    }

    result += matches.prefix().str();
    str = matches.suffix().str();
  }

  str = result;
}


} // string
} // utility
} // dnw
