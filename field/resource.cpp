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
#include "field/resource.hpp"


namespace dnw {
namespace field {


Resource::Resource(Node const &node, String const &field)
  : Field(node, field)
{
}

Index Resource::resourceCount() const
{
  return count();
}

String Resource::resourceName(Index index) const
{
  return name(index);
}

String Resource::resource(String const &name) const
{
  return data(name);
}

String Resource::resourcePath(Index index) const
{
  auto name = resourceName(index);

  return path(name);
}

bool Resource::resourceExists(String const &name) const
{
  return exists(name);
}

bool Resource::editResource(String const &name, String const &data) const
{
  return edit(name, data);
}

bool Resource::removeResource(String const &name) const
{
  return remove(name);
}

bool Resource::moveResourceToChild(Index index, String const &name) const
{
  auto child = node.node(index);

  if (child == nullptr)
    return false;
  if (child->isSame(node) == true)
    return false;

  Resource childResource(*child, field);

  if (childResource.resourceExists(name) == true)
    return false;

  if (childResource.editResource(name, resource(name)) == false)
    return false;

  return removeResource(name);
}

bool Resource::moveResourceToParent(String const &name) const
{
  auto parent = node.parent();

  if (parent == nullptr)
    return false;
  if (parent->isSame(node) == true)
    return false;

  Resource parentResource(*parent, field);

  if (parentResource.resourceExists(name) == true)
    return false;

  if (parentResource.editResource(name, resource(name)) == false)
    return false;

  return removeResource(name);
}


} // field
} // dnw


