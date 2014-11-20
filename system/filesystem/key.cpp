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

#include "system/filesystem/key.hpp"
#include "utility/string.hpp"
#include <sstream>
#include <boost/lexical_cast.hpp>


namespace dnw {
namespace system {
namespace filesystem {


Key::Key(String const &str)
  : indices()
{
  using Strings = std::vector<String>;
  using dnw::utility::string::split;

  Strings items;
  split(str, delimiter(), items);

  for (auto &item : items)
    push(boost::lexical_cast<unsigned>(item));
}

Index Key::depth() const
{
  return indices.size();
}

Index Key::index(Level level) const
{
  return indices[level];
}

Index Key::last() const
{
  return index(depth() - 1);
}

void Key::pop()
{
  if (indices.empty())
    return;

  indices.pop_back();
}

void Key::push(Index index)
{
  indices.push_back(index);
}

bool Key::empty() const
{
  return depth() == 0;
}

String Key::string() const
{
  std::stringstream ss;

  for (unsigned i = 0; i < depth(); ++i) {
    if (i)
      ss << delimiter();
    ss << index(i);
  }

  return ss.str();
}

bool Key::same(Key const &key) const
{
  if (key.depth() == depth()) {
    for (unsigned i = 0; i < depth(); ++i)
      if (key.index(i) != index(i))
        return false;

    return true;
  }

  return false;
}

bool Key::childOf(Key const &key) const
{
  return key.parentOf(*this);
}

bool Key::parentOf(Key const &key) const
{
  if (key.depth() > depth()) {
    for (unsigned i = 0; i < depth(); ++i)
      if (key.index(i) != index(i))
        return false;

    return true;
  }

  return false;
}


char Key::delimiter()
{
  return '_';
}


} // filesystem
} // system
} // dnw
