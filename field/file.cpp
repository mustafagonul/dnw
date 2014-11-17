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

#include "field/file.hpp"
#include "system/device.hpp"


namespace dnw {
namespace field {


File::File(Device const &device)
  : Field(device, "file")
{
}

File::Index File::fileCount() const
{
  return count();
}

File::String File::fileName(Index index) const
{
  return name(index);
}

File::String File::file(String const &name) const
{
  return data(name);
}

File::String File::filePath(Index index) const
{
  auto name = fileName(index);

  return path(name);
}

bool File::fileExists(String const &name) const
{
  return exists(name);
}

bool File::editFile(String const &name, String const &data) const
{
  return edit(name, data);
}

bool File::removeFile(String const &name) const
{
  return remove(name);
}

bool File::moveFileToChild(Index index, String const &name) const
{
  auto child = device.nodeDevice(index);

  if (child == nullptr)
    return false;
  if (child->isSame(device) == true)
    return false;

  File childFile(*child);

  if (childFile.fileExists(name) == true)
    return false;

  if (childFile.editFile(name, file(name)) == false)
    return false;

  return removeFile(name);
}

bool File::moveFileToParent(String const &name) const
{
  auto parent = device.parentDevice();

  if (parent == nullptr)
    return false;
  if (parent->isSame(device) == true)
    return false;

  File parentFile(*parent);

  if (parentFile.fileExists(name) == true)
    return false;

  if (parentFile.editFile(name, file(name)) == false)
    return false;

  return removeFile(name);
}


} // field
} // dnw
