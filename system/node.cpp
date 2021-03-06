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
#include <memory>


namespace dnw {
namespace system {


Node::Node()
{
}

Node::~Node()
{
}

Node::NodePtr Node::node(Index index) const
{
  if (index >= nodeCount())
    return nullptr;

  return clone(nodeKey(index));
}

Node::NodePtr Node::last() const
{
  auto count = nodeCount();

  if (count == 0)
    return nullptr;

  return clone(nodeKey(count - 1));
}

Node::NodePtr Node::parent() const
{
  return clone(parentKey());
}

Node::NodePtr Node::root() const
{
  return clone(rootKey());
}

bool Node::removeNode(Index index) const
{
  if (moveNodeToLast(index) == false)
    return false;

  if (popNode() == false) {
    moveNodeToLast(index);
    return false;
  }

  return true;
}

bool Node::moveNode(Index from, Index to) const
{
  unsigned count = nodeCount();

  if (count == 0)
      return false;

  if (from >= count)
    return false;

  if (to >= count)
    return false;

  while (from != to) {
    if (moveNodeDown(from) == false)
      return false; // TODO we should rewind this

    from = (from + 1) % count;
  }

  return true;
}

bool Node::moveNodeUp(Index index) const
{
  if (nodeCount() == 0)
    return false;

  if (index >= nodeCount())
    return false;

  unsigned count = nodeCount();
  unsigned otherIndex = (index - 1 + count) % count;

  return swapNodes(index, otherIndex);
}

bool Node::moveNodeDown(Index index) const
{
  if (nodeCount() == 0)
    return false;

  if (index >= nodeCount())
    return false;

  unsigned count = nodeCount();
  unsigned otherIndex = (index + 1) % count;

  return swapNodes(index, otherIndex);
}

bool Node::moveNodeToLast(Index index) const
{
  if (nodeCount() == 0)
    return false;

  unsigned last = nodeCount() - 1;

  return moveNode(index, last);
}

bool Node::moveLastToNode(Index index) const
{
  if (nodeCount() == 0)
    return false;

  unsigned last = nodeCount() - 1;

  return moveNode(last, index);
}

bool Node::moveNodeToParent(Index index) const
{
  if (moveNodeToLast(index) == false)
    return false;

  if (popNodeToParent() == false) {
    moveNodeToLast(index);
    return false;
  }

  return true;
}

bool Node::moveNodeToNode(Index source, Index destination) const
{
  unsigned count = nodeCount();

  if(count < 2)
    return false;

  if (source >= count)
    return false;

  if (destination >= count)
      return false;

  if (source == destination)
    return false;

  if (moveNodeToLast(source) == false)
    return false;

  if (source < destination)
    --destination;

  if (destination == count - 1)
    --destination;

  if (popNodeToNode(destination) == false) {
    moveNodeToLast(source);
    return false;
  }

  return true;
}


} // system
} // dnw

