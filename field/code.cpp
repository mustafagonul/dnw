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

#include "field/code.hpp"


namespace dnw {
namespace field {


Code::Code(Device const &device)
  : Field(device, "code")
{
}

Code::Index Code::codeCount() const
{
  return count();
}

Code::String Code::codeName(Index index) const
{
  return name(index);
}

Code::String Code::code(String const &name) const
{
  return data(name);
}

bool Code::editCode(String const &name, String const &data) const
{
  return edit(name, data);
}

bool Code::removeCode(String const &name) const
{
  return remove(name);
}


} // field
} // dnw
