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

#include "field/text.hpp"
#include <boost/algorithm/string.hpp>


namespace dnw {
namespace field {


Text::Text(Node const &node, String const &field)
  : Field(node, field)
{
}

bool Text::textExists(String const &language) const
{
  return exists(language);
}

bool Text::editText(String const &language, String const &data) const
{
  return edit(language, data);
}

bool Text::searchText(String const &language, String const &data, bool caseSensitive) const
{
  auto txt = text(language);
  auto exp = data;

  if (caseSensitive == false) {
    boost::to_upper(txt);
    boost::to_upper(exp);
  }

  return txt.find(exp) != String::npos;
}

String Text::text(String const &language) const
{
  return data(language);
}


} // field
} // dnw
