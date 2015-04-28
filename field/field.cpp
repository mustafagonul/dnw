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

#include "system/node.hpp"
#include "field/field.hpp"


namespace dnw {
namespace field {


Field::Field(Node const &n, String const &f)
  : node(n)
  , field(f)
{
}

Index Field::count() const
{
  return node.count(field);
}

bool Field::exists(String const &name) const
{
  return node.exists(field, name);
}

bool Field::remove(String const &name) const
{
  return node.remove(field, name);
}

bool Field::edit(String const &name, String const &data) const
{
  return node.edit(field, name, data);
}

String Field::name(Index index) const
{
  return node.name(field, index);
}

String Field::data(String const &name) const
{
  return node.data(field, name);
}

String Field::path(String const &name) const
{
  return node.path(field, name);
}

Time Field::time(String const &name) const
{
  return node.time(field, name);
}


} // field
} // dnw
