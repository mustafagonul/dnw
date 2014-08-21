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

#include "field/content.hpp"
#include "field/file.hpp"



namespace site {
namespace field {


Content::Content(Device const &device)
  : Field(device, "content")
{
}

bool Content::contentExists(String const &language) const
{
  return exists(language);
}

bool Content::editContent(String const &language, String const &data) const
{
  return edit(language, data);
}

Content::String Content::content(String const &language) const
{
  return data(language);
}

} // field
} // site
