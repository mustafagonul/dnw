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

#include "field/field.hpp"
#include "system/device.hpp"


namespace dnw {
namespace field {


Field::Field(Device const &d, String const &f)
  : device(d)
  , field(f)
{
}

Index Field::count() const
{
  return device.count(field);
}

bool Field::exists(String const &name) const
{
  return device.exists(field, name);
}

bool Field::remove(String const &name) const
{
  return device.remove(field, name);
}

bool Field::edit(String const &name, String const &data) const
{
  return device.edit(field, name, data);
}

String Field::name(Index index) const
{
  return device.name(field, index);
}

String Field::data(String const &name) const
{
  return device.data(field, name);
}

String Field::path(String const &name) const
{
  return device.path(field, name);
}


} // field
} // dnw
