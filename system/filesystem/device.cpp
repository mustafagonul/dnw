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

#include "system/filesystem/device.hpp"
#include "utility/file.hpp"
#include <limits>
#include <memory>
#include <boost/filesystem.hpp>
#include <Wt/WApplication>
#include <Wt/WEnvironment>


namespace fs = boost::filesystem;


namespace dnw {
namespace system {
namespace filesystem {


static std::string rootDirectory();
static std::string tempDirectory();
static fs::path keyToDirectory(Key const &);


Device::Device(Key const &k)
  : dnw::system::Device()
  , m_key(k)
{
}

Device::Device()
  : Device(Key())
{
}

Device::~Device()
{
}

Index Device::nodeCount() const
try {

  unsigned max = std::numeric_limits<unsigned>::max();
  for (unsigned i = 0; i <= max; ++i) {
    Key childKey = key();
    childKey.push(i);

    if (fs::exists(keyToDirectory(childKey)) == false)
      return i;
  }

  return max;
}
catch (...)
{
  return 0;
}

Any Device::currentKey() const
{
  return key().string();
}

Any Device::rootKey() const
{
  return Key().string();
}

/*
FilesystemDevice::String FilesystemDevice::previousKey() const
{
  if (key().count() == 0)
    return key().string();

  auto parent = clone(parentKey());
  auto count = parent->childCount();
  auto index = key().last();
  auto previous = (index + count - 1) % count;

  Key result = key();
  result.pop();
  result.push(previous);

  return result.string();
}

FilesystemDevice::String FilesystemDevice::nextKey() const
{
  if (key().count() == 0)
    return key().string();

  auto parent = clone(parentKey());
  auto count = parent->childCount();
  auto index = key().last();
  auto next = (index + 1) % count;

  Key result = key();
  result.pop();
  result.push(next);

  return result.string();
}
*/

Any Device::parentKey() const
{
  Key pKey = key();

  pKey.pop();

  return pKey.string();
}

Any Device::nodeKey(Index index) const
{
  if (index >= nodeCount())
    return Key().string();

  Key nKey = key();
  nKey.push(index);

  return nKey.string();
}

Device::DevicePtr Device::clone(Any const &any) const
try {
  auto str = boost::any_cast<String>(any);
  Key key(str);

  //checks if the directory exists
  //auto p = keyToDirectory(key);
  //if (fs::exists(p) == false)
  //  return nullptr;

  auto ptr = new Device(key);

  return DevicePtr(ptr);
}
catch (...) {
  return nullptr;
}

bool Device::isSame(Base const &base) const
try {
  auto const &device = dynamic_cast<Device const &>(base);

  return device.key().same(key());
}
catch (...) {
  return false;
}

bool Device::pushNode() const
{
  Key cKey = key();
  cKey.push(nodeCount());

  fs::path path = keyToDirectory(cKey);

  return fs::create_directories(path);
}

bool Device::popNode() const
{
  if (nodeCount() == 0)
    return false;

  Key nKey = key();
  nKey.push(nodeCount() - 1);

  fs::path path = keyToDirectory(nKey);

  return fs::remove_all(path) > 0;
}

bool Device::popNodeToNode(Index index) const
{
  // there should be at least two nodes to perform operation
  if (nodeCount() < 2)
    return false;

  // index cannot be the last node
  if (index >= nodeCount() - 1)
    return false;

  // last node is the source
  Key sourceKey = key();
  sourceKey.push(nodeCount() - 1);

  // other node will destination
  auto nd = nodeDevice(index);
  auto nk = boost::any_cast<String>(nodeKey(index));
  Key destinationKey(nk);
  destinationKey.push(nd->nodeCount());

  // paths
  fs::path source = keyToDirectory(sourceKey);
  fs::path destination = keyToDirectory(destinationKey);

  // moving
  fs::rename(source, destination);

  return true;
}

bool Device::popNodeToParent() const
{
  // if there is no node there is nothing to do
  if (nodeCount() == 0)
    return false;

  auto ck = boost::any_cast<String>(currentKey());
  auto pk = boost::any_cast<String>(parentKey());

  // if there is no parent node, there is nothing to do.
  if (ck == pk)
    return false;

  // source key
  Key sourceKey = key();
  sourceKey.push(nodeCount() - 1);

  // destination key
  Key destinationKey(pk);
  auto pd = parentDevice();
  destinationKey.push(pd->nodeCount());

  // destinations
  fs::path source = keyToDirectory(sourceKey);
  fs::path destination = keyToDirectory(destinationKey);

  // moving
  fs::rename(source, destination);

  return true;
}

bool Device::swapNodes(Index i1, Index i2) const
{
  if (i1 >= nodeCount())
    return false;

  if (i2 >= nodeCount())
    return false;

  if (i1 == i2)
    return true;

  Key k1 = key();
  Key k2 = key();
  k1.push(i1);
  k2.push(i2);

  fs::path temp = keyToDirectory(key()) / tempDirectory();
  fs::path dir1 = keyToDirectory(k1);
  fs::path dir2 = keyToDirectory(k2);

  fs::rename(dir1, temp); // TODO mustafa
  fs::rename(dir2, dir1);
  fs::rename(temp, dir2);

  return true;
}

Index Device::count(String const &field) const
try {
  if (field.empty())
    return 0;

  fs::path p = keyToDirectory(key()) / field;
  fs::directory_iterator iter(p);
  fs::directory_iterator end = fs::directory_iterator();
  unsigned result = 0;

  for (; iter != end; ++iter)
    if (fs::is_regular_file(*iter))
      ++result;

  return result;
}
catch (...)
{
  return 0;
}


bool Device::exists(String const &field, String const &name) const
{
  std::string pStr = path(field, name);

  if (pStr.empty() == true)
    return false;

  fs::path p = pStr;

  return fs::exists(p);
}

bool Device::remove(String const &field, String const &name) const
{
  std::string pStr = path(field, name);

  if (pStr.empty() == true)
    return false;

  fs::path p = pStr;
  fs::remove(p);

  return fs::exists(p) == false;
}

bool Device::edit(String const &field, String const &name, String const & data) const
try {
  if (field.empty())
    return false;
  if (name.empty())
    return false;

  fs::path p = keyToDirectory(key()) / field;
  fs::create_directories(p);

  p /= name;

  dnw::utility::file::write(p.string(), data);

  return fs::exists(p);
}
catch (fs::filesystem_error const &)
{
  return false;
}


String Device::name(String const &field, Index index) const
try {
  if (field.empty())
    return "";

  fs::path p = keyToDirectory(key()) / field;

  fs::directory_iterator iter(p);
  fs::directory_iterator end = fs::directory_iterator();
  unsigned current = 0;

  for (; iter != end; ++iter)
    if (fs::is_regular_file(*iter)) {
      if (current == index)
        return iter->path().filename().string();
      else
        ++current;
    }

  return "";
}
catch (fs::filesystem_error const &)
{
  return "";
}


String Device::data(String const &field, String const &name) const
{
  if (exists(field, name) == false)
    return "";

  std::string p = path(field, name);

  return dnw::utility::file::read(p);
}

String Device::path(String const &field, String const &name) const
try {
  if (name.empty() == true)
    return "";

  fs::path p = keyToDirectory(key());
  p /= field;
  p /= name;

  return p.string(); // TODO mustafa path.make_preferred()
}
catch (...)
{
  return "";
}

Key const &Device::key() const
{
  return m_key;
}

static String rootDirectory()
{
  return "data";
}

static String tempDirectory()
{
  return "temp";
}

static fs::path keyToDirectory(Key const &key)
{
  fs::path result = fs::current_path() / rootDirectory();

  for (unsigned i = 0; i < key.depth(); ++i)
    result /= std::to_string(key.index(i));

  return result;
}


} // filesystem
} // system
} // dnw
